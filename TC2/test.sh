#!/bin/bash

if [ $# -eq 0 ]; then
    echo Entre a pasta das entradas caralho
fi

folder=$1
diffCmd='diff -y --suppress-common-lines -W `tput cols`'

if [ -d folder ]; then
    echo Essa pasta n eh uma pasta meu bom
fi

# Compares the result with the expected output.
for test in `ls $folder/`; do
    echo Teste $test

    tempout=out

    for file in `ls $folder/$test`; do
    Java Main < $folder/$test/$file | tee $tempout
    exitcode=$?
    if [ exitcode -ne 0 ]; then
        echo deu pau!
    fi

    ${diffCmd} $tempout $folder/$test/ > $tempfile

    # Checks if there has been error.
    if [ $? != 0 ]; then
        # Warns the user and outputs the difference.
        echo "[E] Testando $dir: teste ${testId}, diferenças em $output (professor <- -> aluno):"
        cat $tempfile
        echo ""
    else
        # Prints an OK message.
        echo "[I] Testando $dir: teste ${testId}, tudo OK em $output"
    fi

    # Cleanup (deletes the output file and the diff output file).
    rm -f $srcDir/${output} $tempfile


done