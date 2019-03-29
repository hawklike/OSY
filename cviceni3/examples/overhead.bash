#! /bin/bash
############################################################
#  Shell script that demonstrates synchronization overhead # 
############################################################

####################################################
#  Define shell variables 
####################################################
SUM_RC_PT="./sum_raceconds_pt_01"
SUM_MTX_PT="./sum_mutex_pt_01"
SUM_SEM_PT="./sum_sem_pt_01"

SUM_RC_CPP="./sum_raceconds_01"
SUM_MTX_CPP="./sum_mutex_01"
SUM_SEM_CPP="./sum_sem_01"

LINE="----------------------------------------------------------------------------------"

#####################################################
#  Define shell function
#####################################################
overhead() {

  echo
  printf "  n1 = %s    n2 = %s\n" "$(echo $1 | rev | sed -E 's/(...)/\1 /g' | rev )" "$(echo $2 | rev | sed -E 's/(...)/\1 /g' | rev )"

  echo "$LINE"
  echo -e "    Race condition:"
  if [ -x "$SUM_RC_PT" ]  ; then echo -n "      POSIX: " ; { time "$SUM_RC_PT" $1 $2  >/dev/null ; } 2>&1  | tr '\n' '\t' ; echo ; fi
  if [ -x "$SUM_RC_CPP" ] ; then echo -n "      C++:   " ; { time "$SUM_RC_CPP" $1 $2 >/dev/null ; } 2>&1 | tr '\n' '\t'  ; echo ; fi
  echo "$LINE"

  echo -e "    Mutex:"
  if [ -x "$SUM_MTX_PT" ]  ; then echo -n "      POSIX: " ; { time "$SUM_MTX_PT" $1 $2  >/dev/null ; } 2>&1  | tr '\n' '\t' ; echo ; fi
  if [ -x "$SUM_MTX_CPP" ] ; then echo -n "      C++:   " ; { time "$SUM_MTX_CPP" $1 $2 >/dev/null ; } 2>&1 | tr '\n' '\t'  ; echo ; fi
  echo "$LINE"
}

#####################################################
#  Shell script
#####################################################
echo "Overhead of synchronization"

for i in 1000000 10000000 100000000 # 1000000000
do
  overhead $i $((2*i))
done

#####################################################
