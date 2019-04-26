#!/bin/sh
#A bash script to automate testing for the 1927 week 1 lab task

#Clear output file so we don't keep old results
rm time.txt

#Obtain and store the results
for size in 5000 10000 #amount of numbers to be sorted
do
    for repeated in duplicates noDuplicates
    do
        for order in sorted reverseSorted random
        do
          for trial in $(seq 3) #number of trials
            do
                #Depending on what conditions generate the numbers to be tested in file num1

                case "$repeated" in
                    'duplicates')
                        case "$order" in
                            'sorted')
                                ./randl $size | sort -n >num1
                                ;;
                            'reverseSorted')
                                ./randl $size | sort -nr >num1
                                ;;
                            'random')
                                ./randl $size >num1
                                ;;
                        esac
                        ;;
                    'noDuplicates')
                        case "$order" in
                            'sorted')
                                seq 1 $size | sort -n >num1
                                ;;
                            'reverseSorted')
                                seq 1 $size | sort -nr >num1
                                ;;
                            'random')
                                seq 1 $size | sort -R >num1
                                ;;
                        esac
                        ;;
                esac

                (time sort -n  <num1 >/dev/null) 2>&1 | grep "real" | grep -o "[0-9]\.[0-9].." >>sortR
                (time ./usel <num1 >/dev/null) 2>&1 | grep "real" | grep -o "[0-9]\.[0-9].." >>intlR

                rm num1 #clean up
            done
        done
    done
done

#Average the results and output them to a file
for file in usel sortR
do
    echo "Results from $file" >>time.txt
    for size in 1000 5000 10000 25000 50000 #amount of numbers to be sorted
    do
        for repeated in duplicates noDuplicates
        do

            for order in sorted reverse random
            do
                total=0
                i=1
                for trial in `seq 1 5` #number of trials
                do
                    #Concatenate a hyphen '-' in front of i so that head takes it as a flag
                    c="-$i"

                    head $c $file | tail -1 >rd
                    read a <rd

                    #Iterate through i and total
                    i=`expr $i + 1`
                    total=`echo "scale=4; $a + $total"|bc`
                done
                avg=`echo "scale=4; $total / 5"|bc`
                echo "Average for $size numbers $order with $repeated: $avg" >>time.txt
            done
            echo "">>time.txt
        done
    done
done

#clean up
rm usel sortR
