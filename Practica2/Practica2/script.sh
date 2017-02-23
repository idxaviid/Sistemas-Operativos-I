FILE=$1 
k=$2
if [ -f $FILE ]; 
then 
   echo "El archivo $FILE SI existe"
   IFS=$','
   linea=`cat fichero`
   for i in $linea; 
   do 
	for ((j=1; j<=k; j++));
	do
	   echo "$i $j"
        done
   done
else 
   echo "ERROR, el archivo no existe" 
fi 
