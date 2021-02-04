#include <avr/io.h>

    .global analogReadImpl
    .global joystickInitImpl

    .section .text

joystickInitImpl:
    // digital input
    lds r18, DDRB
    cbr r18, (1<<DDB0)
    sts DDRB, r18
    // analog input
    lds r18, ADMUX
    sbr r18, (1<<REFS0)
    sts ADMUX, r18
    lds r18, ADCSRA
    sbr r18, (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0)
    sts ADCSRA, r18
    ret

analogReadImpl:
    // set start read flag
    lds r18, ADCSRA
    sbr r18, (1<<ADSC)
    sts ADCSRA, r18
wait_loop: // wait for the flag to get cleared
    lds r18, ADCSRA
    sbrc r18, ADSC
    rjmp wait_loop
    // return the result
    lds r24, ADCL
    lds r25, ADCH
    ret