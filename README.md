# Controle de Servo com PWM na Raspberry Pi Pico

Este projeto demonstra como controlar um servo motor utilizando PWM na Raspberry Pi Pico. O código é escrito em C com o Pico SDK e implementa um movimento suave do servo entre 0° e 180°, passando por posições fixas de 0°, 90° e 180°.

## Recursos

- **Plataforma:** Raspberry Pi Pico (ou Pico W)
- **Linguagem:** C
- **Ambiente de Desenvolvimento:** VS Code com integração do Pico SDK e simulador Wokwi

## Descrição

O código configura um pino para funcionar em PWM e utiliza esse recurso para controlar a posição de um servo motor. São definidos valores para:
- **0° (mínimo)**
- **90° (meio)**
- **180° (máximo)**

Após posicionar o servo nestes ângulos com um atraso de 5 segundos em cada posição, o firmware entra em um loop infinito realizando uma varredura suave, aumentando e diminuindo gradualmente o duty cycle.

## Hardware

- **Pino de Controle:** `drive_pin` (configurado para o pino 18; para teste com LED RGB, use o pino 11)
- **Servo Motor:** Conectado ao pino de controle com alimentação e terra devidamente conectados.

  
Link do video [aqui ](https://youtu.be/-QUaNPtpCBg).


