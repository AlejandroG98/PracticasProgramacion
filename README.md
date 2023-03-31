# Prácticas de Programación PR3
### ***Asignatura: Prácticas de Programación PR3 - UOC 2020_2<br/><br/>***
# ***Enunciado:<br/>***
Medicamentos (EMA por sus siglas en inglés): Pfizer, Moderna, Astrazeneca y Janssen,
esta última de una sola dosis.<br/>
Para facilitar el proceso de vacunación se va a aumentar la funcionalidad de la aplicación UOCCovid19Vaccine añadiendo lotes de vacunas (VaccinationBatch).
Además se ha decidido indicar en cada paciente (patient) a qué grupo poblacional pertenece. De más a menos prioridad son los siguientes:
1. Personal sanitario en contacto con pacientes
2. Personas de 80 años o más de residencias.
3. Personas adultas de 65 a 79 años
4. Personas con comorbilidades
5. Personal esencial
6. Mayores de 55 años
7. Vacunas para el resto de población. <br/>
Se debe tener en cuenta que: <br/>
● La vacuna “AZD1222” del desarrollador Oxford/Astrazeneca no puede ser implementada en los grupos 2 y 3. <br/>
● La vacuna “JNJ-78436735” del desarrollador Janssen es de una sola dosis. <br/><br/>
En esta tercera práctica se propone la implementación de una lista de lotes de vacunas disponibles de cada país que se irán administrando a los pacientes según su grupo prioritario. <br/>

## ***Ejercicio 1: Creación de una lista de vacunas [35%] <br/>***
Junto con el enunciado tenéis el código de la práctica anterior modificado, en el que hemos añadido los archivos vaccinationBatch.h y vaccinationBatch.c. Estos archivos contienen los tipos de datos y las funciones para la gestión de los lotes de vacunas. <br/>
Cada lote (tVaccinationBatch) tiene asociada una vacuna (tVaccine), un número de lote y un número de vacunas. Los lotes de vacunas se guardarán en una lista
(tVaccinationBatchList) donde los nodos serán de tipo tVaccinationBatchListNode. <br/>
A lo largo de éste y el resto de ejercicios, en caso de que no se pueda reservar o liberar memoria mediante las funciones de la librería estándar de C, se devolverá un error con código ERR_MEMORY_ERROR en la función correspondiente – excepto en aquellos funciones que no hagan ninguna llamada a funciones de gestión de memoria dinámica. <br/>
Ver definición de códigos de error en error.h dentro del proyecto del enunciado. <br/>
En caso de ejecución correcta de la función propuesta devolveremos el código OK – excepto en las funciones donde en su enunciado se pide explícitamente el retorno de un valor particular o las funciones que devuelven void. <br/>
Se pide: <br/>
Dada la definición de tVaccinationBatchListNode en el fichero vaccinationBatch.h, implementar las funciones siguientes en el fichero vaccinationBatch.c:<br/>
1. vaccinationBatchList_create(): inicializa una estructura tVaccinationBatchList como una lista vacía.<br/><br/>
2. vaccineBatchList_insert(): Inserta un elemento en la posición indicada por el índice en la lista (empezando por el cero). Si el índice es mayor que el tamaño de
la lista, devolverá ERR_INVALID_INDEX. <br/><br/>
3. vaccineBatchList_delete(): elimina el elemento de la posición indicada por el índice de la lista (empezando por el cero). Si el índice es mayor que el tamaño de
la lista, devolverá ERR_INVALID_INDEX, en cambio si la lista está vacía devolverá ERR_EMPTY_LIST.<br/><br/>
4. vaccineBatchList_get(): devuelve el nodo de la posición indicada por el índice de la lista. En caso de que el índice sea mayor que el tamaño de la lista o esté vacía devolverá NULL.<br/><br/>
5. vaccinationBatchList_empty(): indica si la lista que se le pasa está vacía (true) o, por el contrario, contiene elementos (false).<br/><br/>
6. vaccinationBatchList_free(): elimina todos los elementos de la lista.<br/>
<br/>Una vez implementados todas las funciones especificadas en el ejercicio deberían pasar correctamente todos los test referentes al ejercicio 1 [PR3_EX1_XX]. 
<br/><br/>Los principales conceptos que deben quedar claros después del ejercicio son:<br/>
● Definición de una lista.<br/>

## ***Ejercicio 2: Gestión de las vacunas de un país [35%] <br/>***
En el ejercicio anterior hemos trabajado con las funciones para crear una lista de lotes de vacunas con funciones que nos permiten añadir información. En este ejercicio trabajaremos con un país (tCountry) que ahora tendrá almacenada una lista de lotes de vacunas (tVaccinationBatchList) que deberá administrar en la cola de pacientes (tPatientQueue) a la espera de vacunarse.<br/>
Se pide:<br/>
1. Dada la nueva definición de tCountry con una lista de lotes de vacunas disponibles tVaccinationBatchList en el fichero country.h, implementa las siguientes funciones en el archivo country.c. Nota: para hacer los apartados a y b hay que llamar a las funciones de la segunda parte de este ejercicio.<br/>
a. country_inoculate_first_vaccine: inocula todas las dosis disponibles de cada lote de vacunas a la cola de pacientes a los que no se les haya
administrado ninguna vacuna. Teniendo en cuenta que los grupos a los que puede asignarse cada vacuna. Los lotes vacíos no se han de eliminar de la
lista. Se aplica la vacunación en el orden que hay en la cola de pacientes.<br/>
b. country_inoculate_second_vaccine: inocula todas las dosis disponibles de la lista de lotes de vacunas a la cola de pacientes a los pacientes que no se
les haya administrado la segunda vacuna. Teniendo en cuenta el número de dosis de cada vacuna y que no se pueden administrar vacunas diferentes a
la de la primera dosis. Los lotes vacíos no se han de eliminar de la lista. Se aplica la vacunación en el orden que hay en la cola de pacientes.<br/>
c. country_percentage_vaccinated. Devuelve el tanto por ciento de la cola de pacientes del país que han sido vacunados con todas las dosis (hay vacunas
de dos dosis y vacunas de una dosis) <br/> <br/>
2. Dada la nueva definición de tPatient con un grupo de población en el fichero patient.h, implementa las funciones siguientes en el archivo vaccinationBatch.c:<br/>
a. vaccineBatchList_inoculate_first_vaccine: inocula la primera vacuna de la lista de lotes de vacunas llamando a la función vaccineBatchList_inoculate.<br/>
<br/>b. vaccineBatchList_inoculate_second_vaccine: inocula la segunda vacuna de la lista de lotes de vacunas llamando a la función vaccineBatchList_inoculate.<br/>
<br/>c. vaccineBatchList_inoculate: Función que recorre la lista de lotes que es apropiada para inocularsela al paciente.<br/><br/>
3. Dada la nueva definición de tPatient con un grupo de población en el fichero patient.h, implementa las siguientes funciones en el archivo patient.c:<br/>
a. patient_isSuitableForVaccine: dado un paciente y una vacuna devuelve cierto si la vacuna es adecuada para el paciente, y falso en caso contrario. <br/>
<br/>Una vez implementadas todas las funciones especificadas en el ejercicio, deberían pasar correctamente todos los test referentes al ejercicio 2 [PR3_EX2_XX].<br/><br/> Los principales conceptos que deben quedar claros después del ejercicio son:<br/>
● Cálculos matemáticos básicos utilizando un TAD<br/><br/>

## ***Ejercicio 3: Búsqueda y ordenación [30%] <br/>***
En el trabajo con TAD es habitual realizar recorridos, búsquedas o ordenaciones. En este apartado se pide que implementéis las siguientes funciones:<br/>
1. Implementa la función siguiente en el archivo patient.c:<br/>
a. patientQueue_countPatients_vaccinationBatch(): dado un identificador de lote de una vacuna, devolverá el número de pacientes que han sido
vacunados con ese lote de vacuna. La función debe ser secuencial. <br/><br/>
2. Implementa las funciones siguientes en el archivo vaccinationBatch.c:<br/>
a. vaccineBatchList_quickSortRecursive(): dada una lista desordenada de lotes de vacunas, los ordena según identificador del lote (lotID) y de manera
descendente usando el nombre. Se debe implementar el algoritmo Quicksort (ordenación rápida).<br/>
<br/>b. vaccineBatchList_quicksort(): función que llama a la función recursiva vaccineBatchList_quickSortRecursive.<br/>
Tenéis implementada las funciones vaccineBatchList_swap y vaccineBatchList_getlotID que os pueden ser de utilidad para realizar este ejercicio.<br/>
<br/>Una vez implementadas todas las funciones especificadas en el ejercicio deberían pasar correctamente todos los test referentes al ejercicio 3 [PR3_EX3_XX].<br/>
<br/>Los principales conceptos que deben quedar claros después del ejercicio son:<br/>
● Búsquedas dentro de una cola<br/>
● Ordenación de una lista con quicksort.<br/>
