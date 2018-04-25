#!bin/bash
function suma
{
	let resultado=n1+n2
}

function resta
{
	let resultado=$1-$2
}

function multi
{
	let resultado=$1*$2
}

function divi
{
	let resultado=n1/n2
}

echo "1. Suma"
echo "2. Resta"
echo "3. Multiplicacion"
echo "4. Division"
echo "Opcion: "
read opcion

echo "Escribe el primer numero: "
read n1
echo "Escribe el segundo numero: "
read n2

case $opcion in
	1)
	suma;;
	2)
	resta $n1 $n2;;
	3)
	multi $n1 $n2;;
	4)
	divi;;
	*)
	echo "opcion no valida";;
esac

echo "Resultado = $resultado"

#tarea para el martes
# Circuito en protoboard, 7 LEDS, display 7s cc, puntas osciloscopio
# GPIO0 - GPIO6 -> PINES 
#	GPIO_0 -> 220ohm -> LED -> GND | A
#	GPIO_1 -> 220ohm -> LED -> GND | B
#	GPIO_2 -> 220ohm -> LED -> GND | C
#	GPIO_3 -> 220ohm -> LED -> GND | D
#	GPIO_4 -> 220ohm -> LED -> GND | E
#	GPIO_5 -> 220ohm -> LED -> GND | F
#	GPIO_6 -> 220ohm -> LED -> GND | G
#
#
#
#
#
#
#
