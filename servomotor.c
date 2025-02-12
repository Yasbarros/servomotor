#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include <stdio.h>

#define SERVO_CTRL_PIN 18  // Se desejar testar com LED RGB, altere para 11

const uint32_t PWM_PERIOD_VALUE = 62500;
const float PWM_DIVISOR_VALUE = 40.0f;

// Protótipos das funções
void servoPWMSetup(void);
void servoPulseSet(float pulseFraction, uint32_t delayMs);

int main(void) {
    // Definindo os limites e incremento para a fração de pulso do servo
    const float PULSE_MIN = 0.025f;    // Posição 0°
    const float PULSE_MID = 0.0735f;   // Posição 90°
    const float PULSE_MAX = 0.12f;     // Posição 180°
    const float PULSE_INCREMENT = 0.00025f;

    // Inicializa a comunicação e o stdio
    stdio_init_all();

    // Configura o PWM para controle do servo
    servoPWMSetup();

    // Movimenta o servo para posições específicas
    servoPulseSet(PULSE_MAX, 5000);  // Aproximadamente 180°
    servoPulseSet(PULSE_MID, 5000);  // Aproximadamente 90°
    servoPulseSet(PULSE_MIN, 5000);  // Aproximadamente 0°

    // Loop infinito para varredura suave do movimento do servo
    while (true) {
        // Incremento de 0° até 180°
        for (float currentPulse = PULSE_MIN; currentPulse <= PULSE_MAX; currentPulse += PULSE_INCREMENT) {
            servoPulseSet(currentPulse, 10);
        }
        // Decremento de 180° até 0°
        for (float currentPulse = PULSE_MAX; currentPulse >= PULSE_MIN; currentPulse -= PULSE_INCREMENT) {
            servoPulseSet(currentPulse, 10);
        }
    }

    return 0;
}

// Função para configurar o PWM no pino do servo
void servoPWMSetup(void) {
    gpio_set_function(SERVO_CTRL_PIN, GPIO_FUNC_PWM);              // Ativa a função PWM no pino
    uint sliceIndex = pwm_gpio_to_slice_num(SERVO_CTRL_PIN);          // Obtém o slice PWM associado
    pwm_set_clkdiv(sliceIndex, PWM_DIVISOR_VALUE);                    // Configura o divisor do clock do PWM
    pwm_set_wrap(sliceIndex, PWM_PERIOD_VALUE);                       // Define o período do PWM
    pwm_set_enabled(sliceIndex, true);                                // Habilita o PWM
}

// Função para atualizar o pulso (duty cycle) do PWM e aplicar um atraso
void servoPulseSet(float pulseFraction, uint32_t delayMs) {
    uint32_t pwmLevel = (uint32_t)(PWM_PERIOD_VALUE * pulseFraction);
    pwm_set_gpio_level(SERVO_CTRL_PIN, pwmLevel);
    sleep_ms(delayMs);
}
