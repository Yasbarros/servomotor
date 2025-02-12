#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include <stdio.h>

#define drive_pin 18

const uint32_t max_count_pwm = 62500;
const float clk_div_pwm = 40.0f;

// protótipos das funções
void init_sinal_pwm(void);
void ajusta_pulso(float fator, uint32_t atraso);

int main(void) {
    // valores que definem a posição do servo:
    // inicio: posição 0°, meio: 90°, fim: 180°
    const float inicio = 0.025f;
    const float meio = 0.0735f;
    const float fim = 0.12f;
    const float delta = 0.00025f;

    stdio_init_all();
    init_sinal_pwm();

    ajusta_pulso(fim, 5000);   // aproximação de 180°
    ajusta_pulso(meio, 5000);  // aproximação de 90°
    ajusta_pulso(inicio, 5000);   // aproximação de 0°

    // loop para varredura contínua do servo de 0° a 180° e retorno
    while (true) {
        // aumenta gradualmente a posição do servo
        for (float valor_atual = inicio; valor_atual <= fim; valor_atual += delta) {
            ajusta_pulso(valor_atual, 10);
        }
        // diminui gradualmente a posição do servo
        for (float valor_atual = fim; valor_atual >= inicio; valor_atual -= delta) {
            ajusta_pulso(valor_atual, 10);
        }
    }
    return 0;
}

// configura o pino para funcionar com pwm
void init_sinal_pwm(void) {
    gpio_set_function(drive_pin, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(drive_pin);
    pwm_set_clkdiv(slice, clk_div_pwm);
    pwm_set_wrap(slice, max_count_pwm);
    pwm_set_enabled(slice, true);
}

// ajusta o pulso do pwm com base no fator e espera o atraso especificado
void ajusta_pulso(float fator, uint32_t atraso) {
    uint32_t nivel = (uint32_t)(max_count_pwm * fator);
    pwm_set_gpio_level(drive_pin, nivel);
    sleep_ms(atraso);
}
