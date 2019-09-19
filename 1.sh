#!/bin/bash
while true :
do
	echo -e "\n1. CREATE FILE"
	echo "2. DISPLAY FILE"
	echo "3. INSERT RECORD"
	echo "4. SEARCH RECORD"
	echo "5. DELETE RECORD"
	echo "6. MODIFY RECORD"
	echo "7. EXIT"

	read ch

	case "$ch" in 

		1)	#echo ""
			echo -ne "\nPlease enter the filename : "
			read filename
			while [ -e $filename.txt ]
			do
				echo -ne "\nFile alreasy exists !!! Please enter new name : "
				read filename
			done
			touch "${filename}.txt"
			echo -e "NAME \tROLL NO \tCLASS \tPHONE NO">>$filename.txt

			;;

		2)	echo ""
			cat "${filename}.txt"

			;;

		3)	bool=1
			while [ $bool -ne 0 ]
			do
				#echo "" 
				echo -ne "\nName of the student: "
				read name
				echo -n "Roll no. of the student: "
				read rollno
				echo -n "Class of the student: "
				read class
				echo -n "Phone no. of the student: "
				read phno
				echo -e "$name \t$rollno \t\t$class \t$phno">>$filename.txt
				echo -ne "\nDO YOU WANT TO INSERT ANOTHER RECORD?[1-Yes|0-No]:"
				read bool
			done

			;;

		4)	echo ""
			cat "${filename}.txt"

			echo -ne "\nEnter the Roll no to search for : "
			read rn
			echo "" 
			grep -iw "${rn}" $filename.txt
			if [ $? -ne 0 ]
			then
				echo "Roll No not found"
			fi

			;;

		5)	echo ""
			cat "${filename}.txt"

			echo -ne "\nEnter a Roll no to delete : "
			read rn
			grep -ivw "$rn" $filename.txt>file1.txt
			grep -iw "${rn}" $filename.txt
			if [ $? -ne 0 ]
			then
				echo -e "\nRoll No not found"
			else
				echo -e "\nRecord deleted successfully"
			fi
			mv file1.txt "$filename.txt"

			;;

		6)	echo ""
			cat "${filename}.txt"

			echo -en "\nEnter a Roll no to modify : "
			read rn
			grep -ivw "$rn" $filename.txt>file1.txt
			grep -iw "${rn}" $filename.txt
			if [ $? -ne 0 ]
			then
				echo -e "\nRoll No not found"
			else
				echo -ne "\nName of the student: "
				read name
				echo -n "Class of the student: "
				read class
				echo -n "Phone no. of the student: "
				read phno
				echo -e "$name \t$rn \t\t$class \t$phno">>file1.txt
				echo -e "\nRoll no modified successfully"
			fi
			mv file1.txt "$filename.txt"

			;;

		7) exit 1

	esac
done