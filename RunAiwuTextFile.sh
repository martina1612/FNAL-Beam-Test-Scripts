############################################################
#		 To Do List	
#
# 1. Add the Brian's macros for analyzing efficiency 
#
#
############################################################
#		Basic Info about this Macro
#
#
#
#
############################################################

source /afs/cern.ch/sw/lcg/external/gcc/4.8/x86_64-slc6/setup.sh
source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.04.02/x86_64-slc6-gcc48-opt/root/bin/thisroot.sh
IRunNo=$1
FRunNo=$2
ILat=15
FLat=30
RunCounter=$IRunNo
if [[ $IRunNo -le 1587 ]]; then
	PathOfInputData=/afs/cern.ch/user/r/rasharma/work/public/GEMTestBeam/Ntuples/H2TestBeam/R306_R407	# PATH FOR H2 TEST BEAM
else
	PathOfInputData=/afs/cern.ch/user/r/rasharma/work/public/GEMTestBeam/Ntuples/H4TestBeam			# PATH FOR H4 TEST BEAM
fi	
PathOfInputData=/media/martina/7f8a29ea-7ffe-494d-b7bb-40967dfc9284/FNAL-Beam-Test-Scripts-B2B_2016TB/RootFiles

    #/*
    # * EfficiencyType : If want to calculate efficiency of each GE11's independently
    # *			Using trigger from hardware only put it equal to 0
    # *
    # *			If want to trigger it using two of the reference tracker 
    # *			put it = 1
    # *
    # *			if want to trigger it only when it passes from all three reference
    # *			tracker then put it = 2
    # */

EfficiencyType=2

    #/*
    # * TrkOnly	    : If you want output text file in which there are hit iff there is 
    # *		      hit only in all three tracker then put this = 1
    # *		    
    # *		      If you want to get hit iff there is hit in all tracker as well
    # *		      as in GE11's then put this = 0
    # */
TrkOnly=0

if [[ $EfficiencyType == 0 ]]; then
	OutputEffFileName="GE11s_Efficiency_Independent.txt"
	info="Independent"
	info_g3="PMTs"
fi
if [[ $EfficiencyType == 1 ]]; then
	OutputEffFileName="GE11s_Efficiency_If_Hit_2_Trk.txt"
	info="HitOnly2Trk"
	info_g3="Trk"
fi
if [[ $EfficiencyType == 2 ]]; then
	OutputEffFileName="GE11s_Efficiency_Hit_all_3_Trk.txt"
	info="HitAll3Trk"
	info_g3="Trk"
fi

EffFileName_geq1Cluster="./EfficiencyTxtFiles/g3_Efficiency_geq1Cluster_${info_g3}_R${IRunNo}_R${FRunNo}.txt"

if [ -f $EffFileName_geq1Cluster ]; then
	rm $EffFileName_geq1Cluster
	echo "$EffFileName_geq1Cluster already exists... Removed."
else
	echo "$EffFileName_geq1Cluster does not exist. New file will be created."
fi

FileList_NrClusters="./NumberOfClusters/FileList_NumberOfClusters_R${IRunNo}_R${FRunNo}.txt"

if [ -f $FileList_NrClusters ]; then
	rm $FileList_NrClusters
	echo "$FileList_NrClusters already exists... Removed."
else
	echo "$FileList_NrClusters does not exist. New file will be created."
fi

function make_dir
{
#	------------------------------------------------------------------------
#	It Checks IF the output data directory exists or not
#	No Arguments
#	------------------------------------------------------------------------

	if [ -d "${1}" ]; then
		echo "Directory ${1} Exists......."
	else
		mkdir ${1}
		echo "Directory ${1} Created................."
	fi
}	# end of make_dir


rm GE11s_Effeciency_Info.txt

make_dir HitTxtFiles
make_dir RootFiles
make_dir ResidualFiles
make_dir ShiftParameterFiles
make_dir EfficiencyTxtFiles
make_dir NumberOfClusters

echo -e "RunName\t\t\t\t\t\t\t\t GE11_IV_GIF \t GE11_IV \t GE11_V" > ${OutputEffFileName}
while [ $RunCounter -le $FRunNo ]
do
    if [[(($RunCounter -le 9))]]; then
        file=000$RunCounter
    else
        if [[(($RunCounter -le 99))]]; then
            file=00$RunCounter
        else
            if [[(($RunCounter -le 999))]]; then
                file=0$RunCounter
            else
                file=$RunCounter
            fi
        fi
    fi
    if [[ $RunCounter != 6 && $RunCounter != 7 && $RunCounter != 11 && $RunCounter != 39 ]]    #to exclude runs from the loop
    	then
    	for dir in $PathOfInputData/Run$file*/; do	    # Start of dir for loop
		echo "===============================================:"
		echo "Directory name : "$dir
		echo "Base name : "$(basename $dir)
		RunName=$(basename $dir)
		for rootfile in $dir/CRC*.root;do	# Start of rootfile for loop
		    echo "Root file name : "$rootfile
		    ./CreateHeader.sh $rootfile rd51tbgeo
#		    if [[ $RunCounter -le 1587 ]]; then
		    	root -l -b -q GetHitTxtFile_H2.C\(\"${rootfile}\",\"${RunName}\",${EfficiencyType},${TrkOnly},\"${EffFileName_geq1Cluster}\",\"${FileList_NrClusters}\"\)
#		    else
#		    	root -l -b -q GetHitTxtFile_H4.C\(\"${rootfile}\",\"${RunName}\",${EfficiencyType},${TrkOnly}\)
#		    fi
		done	# END of rootfile for loop
    	done	# END of dir for loop
	fi       #if condition to exclude one run from the loop
    ((++RunCounter))	# increment counter for while loop
done			# while loop ends
cp ${OutputEffFileName} GE11s_Effeciency_${info}_R${IRunNo}_R$FRunNo.txt
mv GE11s_Effeciency_${info}_R${IRunNo}_R$FRunNo.txt EfficiencyTxtFiles/

echo "file(s) of interest:"
rm EfficiencyTxtFiles/FilesToAnalyze.txt
echo "GE11s_Effeciency_${info}_R${IRunNo}_R$FRunNo.txt" >> EfficiencyTxtFiles/FilesToAnalyze.txt

while [ $ILat -le $FLat ]
do
	rm EfficiencyTxtFiles/GE11s_Effeciency_${info}_R${IRunNo}_R${FRunNo}_Lat${ILat}.txt
	grep "Lat$ILat" EfficiencyTxtFiles/GE11s_Effeciency_${info}_R${IRunNo}_R$FRunNo.txt >> EfficiencyTxtFiles/GE11s_Effeciency_${info}_R${IRunNo}_R${FRunNo}_Lat${ILat}.txt
	outputFile=EfficiencyTxtFiles/GE11s_Effeciency_${info}_R${IRunNo}_R${FRunNo}_Lat${ILat}.txt
	outputFile_short=EfficiencyTxtFiles/GE11s_Effeciency_${info}_R${IRunNo}_R${FRunNo}_Lat${ILat}.txt

	if [[ $(stat -c%s "$outputFile") -le 46 ]]; then
		rm $outputFile
	else
		echo "vim $outputFile"
		echo "GE11s_Effeciency_${info}_R${IRunNo}_R${FRunNo}_Lat${ILat}.txt" >> EfficiencyTxtFiles/FilesToAnalyze.txt
	fi

	ILat=$[$ILat+1]
done 	# End of while loop

cp EfficiencyTxtFiles/FilesToAnalyze.txt EfficiencyTxtFiles/FilesToAnalyze_R${IRunNo}_R${FRunNo}.txt

#echo "To Make Efficiency Curves Execute In Terminal:"
#echo "./analyzeEff.sh"

#===========START: Adding efficiency calculation at the end of file EffFileName_geq1Cluster==========================
filename=$EffFileName_geq1Cluster

readline_count=0
N=0
trigger_count=0
triple_count=0

while read -d "	" entry; 
do
   entryM2=$entryM1
   entryM1=$lastentry
   lastentry=$entry
   
   if [[ $entryM2 == "Run"* ]] ; then
	N=$((N+1))
	trigger_count=$(($trigger_count+$entryM1))
	triple_count=$(($triple_count+$lastentry))
   fi
   readline_count=$(($count+1))
done < $filename


printf "\nefficiency\terror" >> $filename
eff=$(bc <<< "scale = 8 ; $triple_count/$trigger_count")
temp=$(bc <<< "scale = 8 ; $eff*(1-$eff)/$triple_count")
#bc <<< "scale = 6 ; sqrt ( $temp )"
error=$(bc <<< "scale = 8 ; sqrt ( $temp )")
printf "\n$eff\t$error" >> $filename

printf "\n\n"
echo "Find a first evaluation of efficiency in"
echo "$EffFileName_geq1Cluster"
echo "It uses: detectors with at least 1 cluster, no position matching between detectors."
printf "\n\n"
#===========END: Adding efficiency calculation at the end of file EffFileName_geq1Cluster==========================


#=============START: merging rootfiles of numberofclusters for single runs into a rootfile for all runs================
rootfile_NrClusters_allRuns="${FileList_NrClusters}"
rootfile_NrClusters_allRuns=${rootfile_NrClusters_allRuns/FileList_}
rootfile_NrClusters_allRuns=${rootfile_NrClusters_allRuns/.txt/.root}
list="$(< "$FileList_NrClusters")"
list=$(echo $list | tr -d '\n')
rm $rootfile_NrClusters_allRuns
echo "hadd $rootfile_NrClusters_allRuns $list"
hadd $rootfile_NrClusters_allRuns $list

#to normalize histograms
root -l -b -q NormalizeHist.C\(\"${rootfile_NrClusters_allRuns}\"\)

#=============Useful outputs for user============================
printf "\n\n"
echo -e "Some outputs:\n"
echo "A first evaluation of efficiency in"
echo "$EffFileName_geq1Cluster"
echo "It uses: detectors with at least 1 cluster, no position matching between detectors."
printf "\n"
echo "Number of clusters in"
echo "$rootfile_NrClusters_allRuns"
printf "\n\n\n"