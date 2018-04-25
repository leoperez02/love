#!bin/bash

echo "Hoola mundo ..."
echo "suma 3 +7 = $[3+4]"
echo "otra suma $((3+4))"

var1=4
var2=4

echo "var1 = $var1"
echo "var2 = $var2"

suma=$var1+$var2

echo "suma = $suma"

let suma=$var1+$var2
echo "otra suma = $suma"

suma=$[$var1+$var2]
echo "corchetes otra suma = $suma"

# con parentesis $(($var1+$var2))
