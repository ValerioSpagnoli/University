from threading import Thread
import traceback
import ctypes
import sys
import os

def tester_fun(function, input_data, output_data):

    """

    :param function: funzione da testare
    :param input_data: input in formato tupla
    :param output_data: output
    :return:
    """

    # secondi disponibili per l'esecuzione della funzione
    timeout = 2

    print('Test funzione:',function.__name__,'\n')
    
    print('Input funzione:',str(input_data)[1:-1],'\n')

    print('Output atteso:\n', output_data, '\n')

    # BASIC CHECKS su input ed output del tester
    if not isinstance(input_data, list):
        print("ERRORE: l'input data deve essere fornito all'interno di una lista")
        return -1

    if len(input_data)==0 or output_data == None:
        print("ERRORE: input o output non regolare")
        return -1

    print("-"*5 + ' print interne funzione ' + "-"*5 + '\n')

    result_container = []

    # comandi sospensione print all'interno delle funzioni
#    stdout = sys.stdout
#    null = open(os.devnull, 'w')
#    sys.stdout = null


    # la funzione viene eseguita all'interno di un thread, in modo da gestire i loop
    t = Thread(target=helper_tester_function, args=(function, input_data, result_container))
    t.daemon = True
    t.start()
    t.join(timeout)
    # se il thread è ancora alive allo scadere del timeout, probabilmente vi è un loop
    if t.isAlive():
        terminate_thread(t)
        print("-"* 34 + "\n")

#        sys.stdout = stdout    # decommentare nel caso si disattivino le print
        print('La funzione sta impiegando più del previsto a fornire il suo output, potrebbe essere presente un ciclo infinito\n')
        print('Risultato Test: NEGATIVO'+'\n\n'+'*'*30+'\n')
        return 0

    # il risultato o l'eccezione generata vengono inseriti in result_container
    else:
#        sys.stdout = stdout    # decommentare nel caso si disattivino le print
        # nessun valore di ritorno
        if result_container[0] == None:
            print("-"* 34 + "\n")
            print('La funzione non ha ritornato nessun output (None), controllare di aver inserito il comando return\n')
            print('Risultato Test: NEGATIVO'+'\n\n'+'*'*30+'\n')
            return 0


        # in caso di eccezione
        elif isinstance(result_container[0],Exception):
            print("-"* 34 + "\n")
            print('La funzione ha lanciato una eccezione durante il test\n')
            print(result_container[1])
            print('Risultato Test: NEGATIVO'+'\n\n'+'*'*30+'\n')
            return 0
        else:
            # in caso di valore di ritorno fornito
            print("-"* 34 + "\n")
            print('Output ottenuto:\n', result_container[0],'\n')
            if output_data != result_container[0]:
                print('Risultato Test: NEGATIVO'+'\n\n'+'*'*30+'\n')
                return 0
            else:
                print('Risultato Test: POSITIVO'+'\n\n'+'*'*30+'\n')
                return 1



def helper_tester_function(function, input_data, return_value_container):
    """

    Funzione interna, definita per gestire le eccezioni
    """
    try:
        returned_value = function(*input_data)
        return_value_container.append(returned_value)
    except Exception as e:
        return_value_container.append(e)
        return_value_container.append(traceback.format_exc())

def terminate_thread(t):
    """

    Funzione interna, termina un thread
    """
    exec = ctypes.py_object(SystemExit)
    res = ctypes.pythonapi.PyThreadState_SetAsyncExc(ctypes.c_long(t.ident), exec)
    if res == 0:
        print("thread not found!")
    elif res > 1:
        ctypes.pythonapi.PyThreadState_SetAsyncExc(ctypes.c_long(t.ident), None)

