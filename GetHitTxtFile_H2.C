/*
 * BUG: Not reading the first event
 *
 * Cleaning of code
 */

#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "ClassReadTree.cc"
#include "TChain.h"
#include "TString.h"
#include "TLorentzVector.h"
#include "TGraphErrors.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
void GetHitTxtFile_H2(const char* inputfile, string RunName , int EfficiencyType , int TrkOnly, string EffFileName_geq1Cluster, string FileList_NrClusters )//main programme
{

    /*
     * EfficiencyType : If want to calculate efficiency of each GE11's independently
     *			Using trigger from hardware only put it equal to 0
     *
     *			If want to trigger it using two of the reference tracker 
     *			put it = 1
     *
     *			if want to trigger it only when it passes from all three reference
     *			tracker then put it = 2
     */

    TChain* t = new TChain("rd51tbgeo");
    t->Add(inputfile);
    //t->Add("CRC-Run0411_Muon_10k_MSPL2_HVScan_710pt1_710pt1_710pt0_T20_T20_T20_Lat22-141011_013955-0.root");
    
    ClassReadTree CRC(t);
    
    Long64_t nentries = t->GetEntries();
    cout<< "Total "<<nentries<<endl;

    string outputtxtfile = "HitTxtFiles/"+RunName+".txt";
    std::ofstream file_out(outputtxtfile);
    std::ofstream file_outEff;
    std::ofstream file_outEff_geq1Cl(EffFileName_geq1Cluster,  ios::out | ios::app);
    std::ofstream file_outFileListNrCl(FileList_NrClusters, ios::out | ios:: app);
    string outputEfficiencyFile;
    if (EfficiencyType == 0 ) outputEfficiencyFile = "Independent";
    if (EfficiencyType == 1 ) outputEfficiencyFile = "If_Hit_2_Trk";
    if (EfficiencyType == 2 ) outputEfficiencyFile = "Hit_all_3_Trk";

    outputEfficiencyFile = "GE11s_Efficiency_"+outputEfficiencyFile+".txt";

    TH1D *hg1x=new TH1D("Number of clusters on g1x","Number of clusters on g1x",6,-0.5,5.5);	TH1D *hg1y=new TH1D("Number of clusters on g1y","Number of clusters on g1y",6,-0.5,5.5);
    TH1D *hg2x=new TH1D("Number of clusters on g2x","Number of clusters on g2x",6,-0.5,5.5);	TH1D *hg2y=new TH1D("Number of clusters on g2y","Number of clusters on g2y",6,-0.5,5.5);
    TH1D *hg3x=new TH1D("Number of clusters on g3x","Number of clusters on g3x",6,-0.5,5.5);	TH1D *hg3y=new TH1D("Number of clusters on g3y","Number of clusters on g3y",6,-0.5,5.5);
    int x = 0;
    
    file_outEff.open(outputEfficiencyFile, std::ios_base::app);
    if (!file_out)
    {
	std::cout << "error: Could not open the file Hit_Position_Info.txt" << std::endl;
    }
    if (!file_outEff)
    {
	std::cout << "error: Could not open the file Hit_Position_Info.txt" << std::endl;
    }
       

    //================================   initialize some of variables   ======================================================
    Long64_t nbytes = 0, nb = 0;
    bool verbose = 0;
//    bool TrkOnly = 1;

    int count_ngeoch_occ = 0;
    int EventNb = 0;
    int g1x_Hit_count = 0 ;
    int g1y_Hit_count = 0 ;
    int g2x_Hit_count = 0 ;
    int g2y_Hit_count = 0 ;
    int g3x_Hit_count = 0 ;
    int g3y_Hit_count = 0 ;
    int g1_Hit_count = 0 ;   
    int g2_Hit_count = 0 ;
    int g3_Hit_count = 0 ;   
    int LC1_Hit_count = 0 ;
    int LC2_Hit_count = 0 ;
    int LC3_Hit_count = 0 ;
    int Trk_count = 0;
    int coinc_Hit_count = 0;
	
	string rootfile = RunName+"_ClusterInfo.root";
	TFile* f = new TFile(rootfile.c_str(),"recreate");

	TH1F* h_ClusterSize_LC1 = new TH1F("h_ClusterSize_LC1","",10,0,10); h_ClusterSize_LC1->SetXTitle("Cluster Size"); h_ClusterSize_LC1->SetYTitle("Frequency");h_ClusterSize_LC1->SetLabelSize(0.045,"XY");h_ClusterSize_LC1->SetTitleSize(0.045,"XY");
	TH1F* h_ClusterSize_LC2 = new TH1F("h_ClusterSize_LC2","",10,0,10); h_ClusterSize_LC2->SetXTitle("Cluster Size"); h_ClusterSize_LC2->SetYTitle("Frequency");h_ClusterSize_LC2->SetLabelSize(0.045,"XY");h_ClusterSize_LC2->SetTitleSize(0.045,"XY");
	TH1F* h_ClusterSize_LC3 = new TH1F("h_ClusterSize_LC3","",10,0,10); h_ClusterSize_LC3->SetXTitle("Cluster Size"); h_ClusterSize_LC3->SetYTitle("Frequency");h_ClusterSize_LC3->SetLabelSize(0.045,"XY");h_ClusterSize_LC3->SetTitleSize(0.045,"XY");


    //================================   Event Loop Starts   ======================================================
    for( int jentry = 0 ; jentry < t->GetEntries() ; jentry++)//	Event Loop Starts
    //for( int jentry = 0 ; jentry < 8 ; jentry++)//	Event Loop Starts
    {
	Long64_t ientry = t->LoadTree(jentry);
	if (ientry < 0) break;
	t->GetEntry(jentry);
	//============================= count number of actual clusters for each Tracker and Large GEMs   =======================================
	/*    
	 *    This loops added because presently Aiwu's framework can only accepts those events for which
	 *    there are only cluster in each tracker and GEM for each event
	 */
	//=========   Check Number of Clusters For g1xcl  ============================
	int NumCluster_g1x = 0;
	//cout<<"CRC. kMax = "<<CRC.kMaxg1xcl<<endl;
	for(int nbcl=0;nbcl<CRC.kMaxg1xcl;nbcl++)
	{
	    if (verbose)
		cout<<CRC.g1xcl_geoposch[nbcl]<<endl;
	    if (CRC.g1xcl_geoposch[nbcl]==0)
		break;
	    NumCluster_g1x += 1;
	} 
	if (NumCluster_g1x != 0 ) 
	{
	    g1x_Hit_count++;
	}
	
	if (verbose)
	    cout<<"Actual number of clusters = "<<NumCluster_g1x<<endl;
	x = NumCluster_g1x;		hg1x->Fill(x,1);

	//=========   END:: Check Number of Clusters For g1xcl    ============================
	//=========   Check Number of Clusters For g1ycl  ============================
	int NumCluster_g1y = 0;
	for(int nbcl=0;nbcl<CRC.kMaxg1ycl;nbcl++)
	{
	    if (verbose)
		cout<<CRC.g1ycl_geoposch[nbcl]<<endl;
	    if (CRC.g1ycl_geoposch[nbcl]==0)
		break;
	    NumCluster_g1y += 1;
	}
	if (NumCluster_g1y !=0 )
	{
	    g1y_Hit_count++;
	}
	
	if (NumCluster_g1x !=0 && NumCluster_g1y !=0)
	{       
	    g1_Hit_count++;
	}
	
	if (verbose)
	    cout<<"Actual number of clusters = "<<NumCluster_g1y<<endl;
    x = NumCluster_g1y;		hg1y->Fill(x,1);

        //=========   END:: Check Number of Clusters For g1ycl    ============================

	//=========   Check Number of Clusters For g2xcl  ============================
      //
      //
      int NumCluster_g2x = 0;
      for(int nbcl=0;nbcl<CRC.kMaxg2xcl;nbcl++)
      {
          if (verbose)
              cout<<CRC.g2xcl_geoposch[nbcl]<<endl;
          if (CRC.g2xcl_geoposch[nbcl]==0)
              break;
          NumCluster_g2x += 1;
}
if (NumCluster_g2x !=0 )
{
           g2x_Hit_count++;
}
 
      if (verbose)
          cout<<"Actual number of clusters = "<<NumCluster_g2x<<endl;
      x = NumCluster_g2x;		hg2x->Fill(x,1);

        // if (NumCluster_g2x != 1) 
        //  continue;

      //
      //
      //=========   END:: Check Number of Clusters For g2xcl    ============================

      //=========   Check Number of Clusters For g2ycl  ============================
      //
      //
      int NumCluster_g2y = 0;
      for(int nbcl=0;nbcl<CRC.kMaxg2ycl;nbcl++)
      {
          if (verbose)
              cout<<CRC.g2ycl_geoposch[nbcl]<<endl;
          if (CRC.g2ycl_geoposch[nbcl]==0)
              break;
          NumCluster_g2y += 1;
}
 if (NumCluster_g2y !=0 )
{
           g2y_Hit_count++;
}
 
if (NumCluster_g2x !=0 && NumCluster_g2y !=0)
    {       g2_Hit_count++;
}

      if (verbose)
          cout<<"Actual number of clusters = "<<NumCluster_g2y<<endl;
	  x = NumCluster_g2y;		hg2y->Fill(x,1);

        // if (NumCluster_g2y != 1) 
        //  continue;


      //=========   END:: Check Number of Clusters For g2ycl    ============================

      //=========   Check Number of Clusters For g3xcl  ============================
      //
      //
      int NumCluster_g3x = 0;
      for(int nbcl=0;nbcl<CRC.kMaxg3xcl;nbcl++)
      {
          if (verbose)
              cout<<CRC.g3xcl_geoposch[nbcl]<<endl;
          if (CRC.g3xcl_geoposch[nbcl]==0)
              break;
          NumCluster_g3x += 1;

}
if (NumCluster_g3x !=0 )
{
           g3x_Hit_count++;
}
 
      if (verbose)
          cout<<"Actual number of clusters = "<<NumCluster_g3x<<endl;
	  x = NumCluster_g3x;		hg3x->Fill(x,1);

        // if (NumCluster_g3x != 1) 
        //  continue;

      //=========   END:: Check Number of Clusters For g3xcl    ============================

      //=========   Check Number of Clusters For g3ycl  ============================
      //
      //
      int NumCluster_g3y = 0;
      for(int nbcl=0;nbcl<CRC.kMaxg3ycl;nbcl++)
      {
          if (verbose)
              cout<<CRC.g3ycl_geoposch[nbcl]<<endl;
          if (CRC.g3ycl_geoposch[nbcl]==0)
              break;
          NumCluster_g3y += 1;
}
 if (NumCluster_g3y !=0 )
{
           g3y_Hit_count++;
}
 if (NumCluster_g3x !=0 && NumCluster_g3y !=0)
    {       g3_Hit_count++;
}

      if (verbose)
          cout<<"Actual number of clusters = "<<NumCluster_g3y<<endl;
	  x = NumCluster_g3y;		hg3y->Fill(x,1);


  //=========   END:: Check Number of Clusters For g3ycl    ============================
  
  //===============================================   Find coincidences for efficiency   ============================================ 
  // Note: in this code there's non difference between cases EfficiencyType=1,2
 
      if (EfficiencyType == 0)
      	{
	Trk_count++;
	if (NumCluster_g3x !=0 && NumCluster_g3y !=0)   coinc_Hit_count++;
	}
      if (EfficiencyType == 1 || EfficiencyType == 2)
      {
      	if ((NumCluster_g1x !=0 && NumCluster_g1y !=0) && (NumCluster_g2x !=0 && NumCluster_g2y !=0))
	{
	Trk_count++;
	   if ((NumCluster_g3x !=0 && NumCluster_g3y !=0))
	   {
	   coinc_Hit_count++;
	   }
        }
      }

      if (verbose)
          cout<<"Hit count on g3 = "<<g3_Hit_count<<endl;
	  cout<<"Trigger events = "<<Trk_count<<endl;
  //========    END:: Find coincidences for efficiency   ======================================================= 		

     //cout<<"EventNb "<<jentry<<endl;
    bool Trigger = 0;

    if (TrkOnly)
{
        if (NumCluster_g1x == 1 &&  NumCluster_g1y == 1 && NumCluster_g2x == 1 && NumCluster_g2y == 1)
        {   Trigger = 1; }      
}
    else
{
        if (NumCluster_g1x == 1 &&  NumCluster_g1y == 1 && NumCluster_g2x == 1 && NumCluster_g2y == 1 && NumCluster_g3x == 1 && NumCluster_g3y == 1)
        { Trigger = 1; }
}

    if (Trigger)
        {
          EventNb += 1;
          if (verbose)
              cout<<"EventNb "<<EventNb<<endl;
              //cout<<"EventNb "<<EventNb<<"\tActual EvtNumber = "<< jentry <<endl;
              //cout<<"EventNb "<<jentry<<endl;
          file_out<<"EventNb "<<EventNb<<endl;
//file_out<<"EventNb "<<EventNb<<"\tActual EvtNumber = "<< jentry <<endl;
      
}


  //================================   Reference Tracker 1 (CRC.g1xcl)   ======================================================
      int channelFired = 0;             //==== ERROR:: ERROR:: ERROR::  I have to forcefully put channelFired = 0 at two places. If not then it behaves strangly.
      count_ngeoch_occ = 0;
    if (Trigger)
      {
//cout<<"final "<<jentry<<endl;
          if (verbose)
              cout<<"g1xcl\t";
          file_out<<"g1xcl\t";
          channelFired = 0;
          for(Int_t nch=0;nch<CRC.kMaxg1xcl;nch++)
          {
              if (CRC.g1xcl_ngeoch[nch]==0)
                  break;
              channelFired +=CRC.g1xcl_ngeoch[nch];

              //cout<<"Channel Fired = "<<channelFired<<endl;
          }
          if (verbose)
              std::cout<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.g1xcl_geoposX[0]<<"\t"<<CRC.g1xcl_geoposch[0]<<"\t";
          file_out<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.g1xcl_geoposX[0]<<"\t"<<CRC.g1xcl_geoposch[0]<<"\t";
          count_ngeoch_occ = 0;

          for(Int_t nch=0;nch<CRC.kMaxg1xcl;nch++)
          {

              if (CRC.g1xcl_ngeoch[nch]==0)
                  break;
              for (int chfird=0;chfird<CRC.g1xcl_ngeoch[nch];chfird++)
              {
//	      		  										cout << "prova6" << endl;
											cout << "count_ngeoch_occ=" << count_ngeoch_occ << "\tchfird=" << chfird << endl;
//					cout << "sizeof((CRC.g1xcl_geoch)[count_ngeoch_occ]) = " << sizeof((CRC.g1xcl_geoch)[count_ngeoch_occ])/sizeof((CRC.g1xcl_geoch)[count_ngeoch_occ][0]) << endl;
		      								cout << "(CRC.g1xcl_geoch)[count_ngeoch_occ][chfird] = " << (CRC.g1xcl_geoch)[count_ngeoch_occ][chfird] << endl;
                  if((CRC.g1xcl_geoch)[count_ngeoch_occ][chfird] == 0)
                      break;

                  if (verbose)
                      std::cout<<(CRC.g1xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  //std::cout<<(CRC.g1xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  file_out<<(CRC.g1xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";

	      }
              count_ngeoch_occ += 1;
          }
          if (verbose)
              std::cout<<std::endl;
          // std::cout<<std::endl;
int g1x = jentry ;
          file_out<<std::endl;
  }

   //================================   END::   Reference Tracker 1 (CRC.g1xcl)   ======================================================

   //================================   Reference Tracker 1 (CRC.g1ycl)   ======================================================
      channelFired = 0;         //==== ERROR:: ERROR:: ERROR::  I have to forcefully put channelFired = 0 at two places. If not then it behaves strangly.
      count_ngeoch_occ = 0;
    if (Trigger)
      {
          if (verbose)
              cout<<"g1ycl\t";
          file_out<<"g1ycl\t";
          channelFired = 0;
          for(Int_t nch=0;nch<CRC.kMaxg1ycl;nch++)
          {
              if (CRC.g1ycl_ngeoch[nch]==0)
                  break;
              channelFired +=CRC.g1ycl_ngeoch[nch];
              //cout<<"Channel Fired = "<<channelFired<<endl;
          }

          if (verbose)
              std::cout<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.g1ycl_geoposY[0]<<"\t"<<CRC.g1ycl_geoposch[0]<<"\t";
          file_out<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.g1ycl_geoposY[0]<<"\t"<<CRC.g1ycl_geoposch[0]<<"\t";
          count_ngeoch_occ = 0;

  cout<<"for loop starts"<<endl;
          for(Int_t nch=0;nch<CRC.kMaxg1xcl;nch++)
          {
	  														cout << "nch = " << nch << "  " ;
              if (CRC.g1ycl_ngeoch[nch]==0)
                  break;
              for (int chfird=0;chfird<CRC.g1ycl_ngeoch[nch];chfird++)
              {
	      										cout << "\tchfird = " << chfird << "\tcount_ngeoch_occ =" << count_ngeoch_occ << endl;
						cout << "sizeof((CRC.g1ycl_geoch)[count_ngeoch_occ])=" << sizeof((CRC.g1ycl_geoch)[count_ngeoch_occ])/sizeof((CRC.g1ycl_geoch)[count_ngeoch_occ][0]) << endl;
cout<<"if loop starting"<<endl;
                  if((CRC.g1ycl_geoch)[count_ngeoch_occ][chfird] == 0)
                      break;
                  if (verbose)
                      std::cout<<(CRC.g1ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  //std::cout<<(CRC.g1ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  file_out<<(CRC.g1ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
              }
              count_ngeoch_occ += 1;
          }
          if (verbose)
              std::cout<<std::endl;
          // std::cout<<std::endl;
          file_out<<std::endl;
 }


   //================================   END::   Reference Tracker 1 (CRC.g1ycl)   ======================================================    


   //================================   Reference Tracker 1 (CRC.g2xcl)   ======================================================
      channelFired = 0;         //==== ERROR:: ERROR:: ERROR::  I have to forcefully put channelFired = 0 at two places. If not then it behaves strangly.
      count_ngeoch_occ = 0;
    if (Trigger)
      {
         if (verbose)
              cout<<"g2xcl\t";
          file_out<<"g2xcl\t";
          channelFired = 0;
          for(Int_t nch=0;nch<CRC.kMaxg2xcl;nch++)
          {
              if (CRC.g2xcl_ngeoch[nch]==0)
                  break;
              channelFired +=CRC.g2xcl_ngeoch[nch];
              //cout<<"Channel Fired = "<<channelFired<<endl;
          }
          if (verbose)
              std::cout<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.g2xcl_geoposX[0]<<"\t"<<CRC.g2xcl_geoposch[0]<<"\t";
          file_out<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.g2xcl_geoposX[0]<<"\t"<<CRC.g2xcl_geoposch[0]<<"\t";
          count_ngeoch_occ = 0;

          for(Int_t nch=0;nch<CRC.kMaxg2xcl;nch++)
          {
              if (CRC.g2xcl_ngeoch[nch]==0)
                  break;
              for (int chfird=0;chfird<CRC.g2xcl_ngeoch[nch];chfird++)
              {
                  if((CRC.g2xcl_geoch)[count_ngeoch_occ][chfird] == 0)
                      break;
                  if (verbose)
                      std::cout<<(CRC.g2xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  //std::cout<<(CRC.g2xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  file_out<<(CRC.g2xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
              }
              count_ngeoch_occ += 1;
          }
          if (verbose)
              std::cout<<std::endl;
          // std::cout<<std::endl;
          file_out<<std::endl;
   }
   //================================   END::   Reference Tracker 1 (CRC.g2xcl)   ======================================================       

   //================================   Reference Tracker 1 (CRC.g2ycl)   ======================================================
      channelFired = 0;         //==== ERROR:: ERROR:: ERROR::  I have to forcefully put channelFired = 0 at two places. If not then it behaves strangly.
      count_ngeoch_occ = 0;
    if (Trigger)
      {
          if (verbose)
              cout<<"g2ycl\t";
          file_out<<"g2ycl\t";
          channelFired = 0;
          for(Int_t nch=0;nch<CRC.kMaxg2ycl;nch++)
          {
              if (CRC.g2ycl_ngeoch[nch]==0)
                  break;
              channelFired +=CRC.g2ycl_ngeoch[nch];
              //cout<<"Channel Fired = "<<channelFired<<endl;
          }
          if (verbose)
              std::cout<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.g2ycl_geoposY[0]<<"\t"<<CRC.g2ycl_geoposch[0]<<"\t";
          file_out<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.g2ycl_geoposY[0]<<"\t"<<CRC.g2ycl_geoposch[0]<<"\t";
          count_ngeoch_occ = 0;
          for(Int_t nch=0;nch<CRC.kMaxg2ycl;nch++)
          {
              if (CRC.g2ycl_ngeoch[nch]==0)
                  break;
              for (int chfird=0;chfird<CRC.g2ycl_ngeoch[nch];chfird++)
              {
                  if((CRC.g2ycl_geoch)[count_ngeoch_occ][chfird] == 0)
                      break;
                  if (verbose)
                      std::cout<<(CRC.g2ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  //std::cout<<(CRC.g2ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  file_out<<(CRC.g2ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
              }
              count_ngeoch_occ += 1;
          }
          if (verbose)
              std::cout<<std::endl;
          // std::cout<<std::endl;
          file_out<<std::endl;
 }
   //================================   END::   Reference Tracker 1 (CRC.g2ycl)   ======================================================    

   //================================   Reference Tracker 1 (CRC.g3xcl)   ======================================================
      channelFired = 0;         //==== ERROR:: ERROR:: ERROR::  I have to forcefully put channelFired = 0 at two places. If not then it behaves strangly.
      count_ngeoch_occ = 0;
    if (Trigger)
      {
          if (verbose)
              cout<<"g3xcl\t";
          file_out<<"g3xcl\t";
          channelFired = 0;
          for(Int_t nch=0;nch<CRC.kMaxg3xcl;nch++)
          {
              if (CRC.g3xcl_ngeoch[nch]==0)
                  break;
              channelFired +=CRC.g3xcl_ngeoch[nch];
              //cout<<"Channel Fired = "<<channelFired<<endl;
          }
          if (verbose)
              std::cout<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.g3xcl_geoposX[0]<<"\t"<<CRC.g3xcl_geoposch[0]<<"\t";
          file_out<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.g3xcl_geoposX[0]<<"\t"<<CRC.g3xcl_geoposch[0]<<"\t";
          count_ngeoch_occ = 0;
          for(Int_t nch=0;nch<CRC.kMaxg3xcl;nch++)
          {
              if (CRC.g3xcl_ngeoch[nch]==0)
                  break;
              for (int chfird=0;chfird<CRC.g3xcl_ngeoch[nch];chfird++)
              {
                  if((CRC.g3xcl_geoch)[count_ngeoch_occ][chfird] == 0)
                      break;
                  if (verbose)
                      std::cout<<(CRC.g3xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  //std::cout<<(CRC.g3xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  file_out<<(CRC.g3xcl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
              }
              count_ngeoch_occ += 1;
          }
          if (verbose)
              std::cout<<std::endl;
          // std::cout<<std::endl;
          file_out<<std::endl;
 }
   //================================   END::   Reference Tracker 1 (CRC.g3xcl)   ======================================================      

   //================================   Reference Tracker 1 (CRC.g3ycl)   ======================================================

      channelFired = 0;         //==== ERROR:: ERROR:: ERROR::  I have to forcefully put channelFired = 0 at two places. If not then it behaves strangly.
      count_ngeoch_occ = 0;
    if (Trigger)
      {
          if (verbose)
              cout<<"g3ycl\t";
          file_out<<"g3ycl\t";
          channelFired = 0;
          for(Int_t nch=0;nch<CRC.kMaxg3ycl;nch++)
          {
              if (CRC.g3ycl_ngeoch[nch]==0)
                  break;
              channelFired +=CRC.g3ycl_ngeoch[nch];
              //cout<<"Channel Fired = "<<channelFired<<endl;
          }
          if (verbose)
              std::cout<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.g3ycl_geoposY[0]<<"\t"<<CRC.g3ycl_geoposch[0]<<"\t";
          file_out<<channelFired<<"\t"<<channelFired<<"\t"<<CRC.g3ycl_geoposY[0]<<"\t"<<CRC.g3ycl_geoposch[0]<<"\t";
          count_ngeoch_occ = 0;
          for(Int_t nch=0;nch<CRC.kMaxg3ycl;nch++)
          {
              if (CRC.g3ycl_ngeoch[nch]==0)
                  break;
              for (int chfird=0;chfird<CRC.g3ycl_ngeoch[nch];chfird++)
              {
                  if((CRC.g3ycl_geoch)[count_ngeoch_occ][chfird] == 0)
                      break;
                  if (verbose)
                      std::cout<<(CRC.g3ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  //std::cout<<(CRC.g3ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
                  file_out<<(CRC.g3ycl_geoch)[count_ngeoch_occ][chfird]<<"\t"<<1<<"\t";
              }
              count_ngeoch_occ += 1;
          }
          if (verbose)
              std::cout<<std::endl;
          // std::cout<<std::endl;
          file_out<<std::endl;
    }
   //================================   END::   Reference Tracker 1 (CRC.g3ycl)   ======================================================    
      //================================	END::	GE1/1  1 (sCMSNS2LC3)   ======================================================     
      //====================== Clear few arrays: Those behaving Strange.	===============================
   /*
    * Here we are clearing few arrays because somehow it is giving strange behaviour
    *
    * Problem:	For each event the size of the following arrays or pointer to array
    *		should be different. But once we get get some array of length 5-6 
    *		then the size of the array fixed to 5-6 and then in next event event 
    *		the size of these array is 1-2 but it is fixed to 5-6 and first two
    *		entry remains from present event but then rest are copied from last 
    *		big array.
    */
      std::fill_n(CRC.g1xcl_ngeoch,sizeof CRC.g1xcl_ngeoch/sizeof(CRC.g1xcl_ngeoch[0]),0);
      std::fill_n(CRC.g1ycl_ngeoch,sizeof CRC.g1ycl_ngeoch/sizeof(CRC.g1ycl_ngeoch[0]),0);
      std::fill_n(CRC.g2xcl_ngeoch,sizeof CRC.g2xcl_ngeoch/sizeof(CRC.g2xcl_ngeoch[0]),0);
      std::fill_n(CRC.g2ycl_ngeoch,sizeof CRC.g2ycl_ngeoch/sizeof(CRC.g2ycl_ngeoch[0]),0);
      std::fill_n(CRC.g3xcl_ngeoch,sizeof CRC.g3xcl_ngeoch/sizeof(CRC.g3xcl_ngeoch[0]),0);
      std::fill_n(CRC.g3ycl_ngeoch,sizeof CRC.g3ycl_ngeoch/sizeof(CRC.g3ycl_ngeoch[0]),0);
      //std::fill_n(CRC.sCMSNS2LC1_ngeoch,sizeof CRC.sCMSNS2LC1_ngeoch/sizeof(CRC.sCMSNS2LC1_ngeoch[0]),0);
      //std::fill_n(CRC.sCMSNS2LC2_ngeoch,sizeof CRC.sCMSNS2LC2_ngeoch/sizeof(CRC.sCMSNS2LC2_ngeoch[0]),0);
      //std::fill_n(CRC.sCMSNS2LC3_ngeoch,sizeof CRC.sCMSNS2LC3_ngeoch/sizeof(CRC.sCMSNS2LC3_ngeoch[0]),0);
      std::fill_n(CRC.g1xcl_geoposch,sizeof  CRC.g1xcl_geoposch/sizeof(CRC.g1xcl_geoposch[0]),0);
      std::fill_n(CRC.g1ycl_geoposch,sizeof  CRC.g1ycl_geoposch/sizeof(CRC.g1ycl_geoposch[0]),0);
      std::fill_n(CRC.g2xcl_geoposch,sizeof  CRC.g2xcl_geoposch/sizeof(CRC.g2xcl_geoposch[0]),0);
      std::fill_n(CRC.g2ycl_geoposch,sizeof  CRC.g2ycl_geoposch/sizeof(CRC.g2ycl_geoposch[0]),0);
      std::fill_n(CRC.g3xcl_geoposch,sizeof  CRC.g3xcl_geoposch/sizeof(CRC.g3xcl_geoposch[0]),0);
      std::fill_n(CRC.g3ycl_geoposch,sizeof  CRC.g3ycl_geoposch/sizeof(CRC.g3ycl_geoposch[0]),0);
      //std::fill_n(CRC.sCMSNS2LC1_geoposch,sizeof CRC.sCMSNS2LC1_geoposch/sizeof(CRC.sCMSNS2LC1_geoposch[0]),0);
      //std::fill_n(CRC.sCMSNS2LC2_geoposch,sizeof CRC.sCMSNS2LC2_geoposch/sizeof(CRC.sCMSNS2LC2_geoposch[0]),0);
      //std::fill_n(CRC.sCMSNS2LC3_geoposch,sizeof CRC.sCMSNS2LC3_geoposch/sizeof(CRC.sCMSNS2LC3_geoposch[0]),0);
      std::fill_n(CRC.g1xcl_geoposX,sizeof  CRC.g1xcl_geoposX/sizeof(CRC.g1xcl_geoposX[0]),0);
      std::fill_n(CRC.g2xcl_geoposX,sizeof  CRC.g2xcl_geoposX/sizeof(CRC.g2xcl_geoposX[0]),0);
      std::fill_n(CRC.g3xcl_geoposX,sizeof  CRC.g3xcl_geoposX/sizeof(CRC.g3xcl_geoposX[0]),0);
      std::fill_n(CRC.g1ycl_geoposY,sizeof  CRC.g1ycl_geoposY/sizeof(CRC.g1ycl_geoposY[0]),0);
      std::fill_n(CRC.g2ycl_geoposY,sizeof  CRC.g2ycl_geoposY/sizeof(CRC.g2ycl_geoposY[0]),0);
      std::fill_n(CRC.g3ycl_geoposY,sizeof  CRC.g3ycl_geoposY/sizeof(CRC.g3ycl_geoposY[0]),0);
      //std::fill_n(CRC.sCMSNS2LC1_geoposY,sizeof CRC.sCMSNS2LC1_geoposY/sizeof(CRC.sCMSNS2LC1_geoposY[0]),0);
      //std::fill_n(CRC.sCMSNS2LC2_geoposY,sizeof CRC.sCMSNS2LC2_geoposY/sizeof(CRC.sCMSNS2LC2_geoposY[0]),0);
      //std::fill_n(CRC.sCMSNS2LC3_geoposY,sizeof CRC.sCMSNS2LC3_geoposY/sizeof(CRC.sCMSNS2LC3_geoposY[0]),0);
    //
    //Trying to use some shortcut method to delete the memory but did not succeed so apply simple method
    //
    //memset(CRC.g1xcl_geoch, 0, sizeof(CRC.g1xcl_geoch[0][0]) * count_ngeoch_occ * 12);
    //memset(CRC.g1xcl_geoch, sizeof(int)*count_ngeoch_occ*12);
    //delete[] g1xcl_geoch; g1xcl_geoch = NULL;
    //================================
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<CRC.kMaxg1xcl;nch++)
    {
	if (CRC.g1xcl_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<CRC.g1xcl_ngeoch[nch];chfird++)
    {
	if((CRC.g1xcl_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	CRC.g1xcl_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<CRC.kMaxg1ycl;nch++)
    {
	if (CRC.g1ycl_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<CRC.g1ycl_ngeoch[nch];chfird++)
    {
	if((CRC.g1ycl_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	CRC.g1ycl_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }    
    //================================
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<CRC.kMaxg2xcl;nch++)
    {
	if (CRC.g2xcl_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<CRC.g2xcl_ngeoch[nch];chfird++)
    {
	if((CRC.g2xcl_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	CRC.g2xcl_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<CRC.kMaxg2ycl;nch++)
    {
	if (CRC.g2ycl_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<CRC.g2ycl_ngeoch[nch];chfird++)
    {
	if((CRC.g2ycl_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	CRC.g2ycl_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }    
    //================================
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<CRC.kMaxg3xcl;nch++)
    {
	if (CRC.g3xcl_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<CRC.g3xcl_ngeoch[nch];chfird++)
    {
	if((CRC.g3xcl_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	CRC.g3xcl_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<CRC.kMaxg3ycl;nch++)
    {
	if (CRC.g3ycl_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<CRC.g3ycl_ngeoch[nch];chfird++)
    {
	if((CRC.g3ycl_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	CRC.g3ycl_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }    
    //================================
    //================================
    count_ngeoch_occ = 0;
    /*
    for(Int_t nch=0;nch<CRC.kMaxsCMSNS2LC1;nch++)
    {
	if (CRC.sCMSNS2LC1_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<CRC.sCMSNS2LC1_ngeoch[nch];chfird++)
    {
	if((CRC.sCMSNS2LC1_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	CRC.sCMSNS2LC1_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<CRC.kMaxsCMSNS2LC2;nch++)
    {
	if (CRC.sCMSNS2LC2_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<CRC.sCMSNS2LC2_ngeoch[nch];chfird++)
    {
	if((CRC.sCMSNS2LC2_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	CRC.sCMSNS2LC2_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }    
    //================================
    count_ngeoch_occ = 0;
    for(Int_t nch=0;nch<CRC.kMaxsCMSNS2LC1;nch++)
    {
	if (CRC.sCMSNS2LC3_ngeoch[nch]==0)
	break;
    for (int chfird=0;chfird<CRC.sCMSNS2LC3_ngeoch[nch];chfird++)
    {
	if((CRC.sCMSNS2LC3_geoch)[count_ngeoch_occ][chfird] == 0)
	    break;
	CRC.sCMSNS2LC3_geoch[count_ngeoch_occ][chfird]= 0;
    }
    count_ngeoch_occ += 1;
    }    
    //================================    
    */
    //====================== END::  Clear few arrays: Those behaving Strange.	===============================	


	  //file_out<<"EventNb "<<EventNb<<"\tActual EvtNumber = "<< jentry <<endl;

	
    }// End Event Loop

f->Write();
f->Close();
//cout.precision(2);
//file_outEff.precision(2);

if (EfficiencyType == 0)
{
file_outEff << RunName <<"\t"<< fixed<<std::setprecision(3)<<
             (float)LC1_Hit_count/(float)nentries<<"+/-0.000\t"<<
             (float)LC2_Hit_count/(float)nentries<<"+/-0.000\t"<<
            (float)LC3_Hit_count/(float)nentries<<"+/-0.000\t\n";
cout << RunName <<"\t"<< fixed<<std::setprecision(3) <<
             (float)LC1_Hit_count/(float)nentries<<"+/-0.000\t"<<
             (float)LC2_Hit_count/(float)nentries<<"+/-0.000\t"<<
            (float)LC3_Hit_count/(float)nentries<<"+/-0.000\t\n";
cout<<"LC1 count = "<<LC1_Hit_count<<"\t"<<"Trk Count = "<<Trk_count<<endl;	  
}
if (EfficiencyType == 1)
{
file_outEff << RunName <<"\t"<< fixed<<std::setprecision(3) <<
             (float)LC1_Hit_count/(float)Trk_count<<"+/-0.000\t"<<
             (float)LC2_Hit_count/(float)Trk_count<<"+/-0.000\t"<<
            (float)LC3_Hit_count/(float)Trk_count<<"+/-0.000\t\n";	  
cout << RunName <<"\t"<< fixed<<std::setprecision(3) <<
             (float)LC1_Hit_count/(float)Trk_count<<"+/-0.000\t"<<
             (float)LC2_Hit_count/(float)Trk_count<<"+/-0.000\t"<<
            (float)LC3_Hit_count/(float)Trk_count<<"+/-0.000\t\n";	  

cout<<"LC1 count = "<<LC1_Hit_count<<"\t"<<"Trk Count = "<<Trk_count<<endl;	  
}
if (EfficiencyType == 2)
{
file_outEff << RunName <<"\t"<< fixed<<std::setprecision(3) <<
             (float)LC1_Hit_count/(float)Trk_count<<"+/-0.000\t"<<
             (float)LC2_Hit_count/(float)Trk_count<<"+/-0.000\t"<<
            (float)LC3_Hit_count/(float)Trk_count<<"+/-0.000\t\n";
cout << RunName <<"\t"<< fixed<<std::setprecision(3) <<
             (float)LC1_Hit_count/(float)Trk_count<<"+/-0.000\t"<<
             (float)LC2_Hit_count/(float)Trk_count<<"+/-0.000\t"<<
            (float)LC3_Hit_count/(float)Trk_count<<"+/-0.000\t\n";
cout<<"LC1 count = "<<LC1_Hit_count<<"\t"<<"Trk Count = "<<Trk_count<<endl;	  
}
if (verbose)
{
cout<<"g1x_Hit=============> "<<g1x_Hit_count<<"\tnentries = "<<nentries<<endl;
cout<<"efficiency_g1x "<<(float) g1x_Hit_count/(float) nentries<<endl;

cout<<"g1y_Hits=============> "<<g1y_Hit_count<<endl;
cout<<"efficiency_g1y "<<(float) g1y_Hit_count/(float) nentries<<endl;

cout<<"g2x_Hits=============> "<<g2x_Hit_count<<endl;
cout<<"efficiency_g2x "<<(float) g2x_Hit_count/(float) nentries<<endl;

cout<<"g2y_Hits=============> "<<g2y_Hit_count<<endl;
cout<<"efficiency_g2y "<<(float) g2y_Hit_count/(float) nentries<<endl;
cout<<"g3x_Hits=============> "<<g3x_Hit_count<<endl;
cout<<"efficiency_g3x "<<(float) g3x_Hit_count/(float) nentries<<endl;

cout<<"g3y_Hits=============> "<<g3y_Hit_count<<endl;
cout<<"efficiency_g3y "<<(float) g3y_Hit_count/(float) nentries<<endl;
cout<<"g1_Hits=============> "<<g1_Hit_count<<endl;
cout<<"efficiency_g1 "<<(float) g1_Hit_count/(float) nentries<<endl;
cout<<"g2_Hits=============> "<<g2_Hit_count<<endl;
cout<<"efficiency_g2 "<<(float) g2_Hit_count/(float) nentries<<endl;
cout<<"g3_Hits=============> "<<g3_Hit_count<<endl;
cout<<"efficiency_g3 "<<(float) g3_Hit_count/(float) nentries<<endl;
cout<<"LC1_Hits=============> "<<LC1_Hit_count<<endl;
cout<<"efficiency_LC1 "<<(float) LC1_Hit_count/(float) nentries<<endl;
cout<<"LC2_Hits=============> "<<LC2_Hit_count<<endl;
cout<<"efficiency_LC2 "<<(float) LC2_Hit_count/(float) nentries<<endl;
cout<<"LC3_Hits=============> "<<LC3_Hit_count<<endl;
cout<<"efficiency_LC3 "<<(float) LC3_Hit_count/(float) nentries<<endl;
}


//===========================Fill text file: for calculate efficiency using detectors with at least 1 cluster====================================================
file_outEff_geq1Cl << RunName << "\t" << Trk_count << "\t" << coinc_Hit_count << "\t" << endl;


//==============================START:: Histograms of Number of cluster====================================================
double scale = 1;
int entries = 0;
hg1x->SetLineColor(1.);
hg1x->SetMarkerColor(1.);
hg1x->GetXaxis()->SetTitle("Number of clusters");
hg1x->GetYaxis()->SetTitle("Entries");
hg1x->GetXaxis()->SetTitleSize(0.04);
hg1x->GetYaxis()->SetTitleSize(0.04);
hg1x->GetXaxis()->SetNdivisions(6);
entries = hg1x->GetEntries();
if ( entries != 0)
	{scale = 100.0/entries;}
else
	{scale = 1;}
//hg1x->Scale(scale);
hg1x->Draw("");

scale = 1;
entries = 0;
hg1y->SetLineColor(1.);
hg1y->SetMarkerColor(1.);
hg1y->GetXaxis()->SetTitle("Number of clusters");
hg1y->GetYaxis()->SetTitle("Entries");
hg1y->GetXaxis()->SetTitleSize(0.04);
hg1y->GetYaxis()->SetTitleSize(0.04);
hg1y->GetXaxis()->SetNdivisions(6);
entries = hg1y->GetEntries();
if ( entries != 0)
	{scale = 100.0/entries;}
else
	{scale = 1;}
//hg1y->Scale(scale);
hg1y->Draw("");

scale = 1;
entries = 0;
hg2x->SetLineColor(1.);
hg2x->SetMarkerColor(1.);
hg2x->GetXaxis()->SetTitle("Number of clusters");
hg2x->GetYaxis()->SetTitle("Entries");
hg2x->GetXaxis()->SetTitleSize(0.04);
hg2x->GetYaxis()->SetTitleSize(0.04);
hg2x->GetXaxis()->SetNdivisions(6);
entries = hg2x->GetEntries();
if ( entries != 0)
	{scale = 100.0/entries;}
else
	{scale = 1;}
//hg2x->Scale(scale);
hg2x->Draw("");

scale = 1;
entries = 0;
hg2y->SetLineColor(1.);
hg2y->SetMarkerColor(1.);
hg2y->GetXaxis()->SetTitle("Number of clusters");
hg2y->GetYaxis()->SetTitle("Entries");
hg2y->GetXaxis()->SetTitleSize(0.04);
hg2y->GetYaxis()->SetTitleSize(0.04);
hg2y->GetXaxis()->SetNdivisions(6);
entries = hg2y->GetEntries();
if ( entries != 0)
	{scale = 100.0/entries;}
else
	{scale = 1;}
//hg2y->Scale(scale);
hg2y->Draw("");

scale = 1;
entries = 0;
hg3x->SetLineColor(1.);
hg3x->SetMarkerColor(1.);
hg3x->GetXaxis()->SetTitle("Number of clusters");
hg3x->GetYaxis()->SetTitle("Entries");
hg3x->GetXaxis()->SetTitleSize(0.04);
hg3x->GetYaxis()->SetTitleSize(0.04);
hg3x->GetXaxis()->SetNdivisions(6);
entries = hg3x->GetEntries();
if ( entries != 0)
	{scale = 100.0/entries;}
else
	{scale = 1;}
//hg3x->Scale(scale);
hg3x->Draw("");

scale = 1;
entries = 0;
hg3y->SetLineColor(1.);
hg3y->SetMarkerColor(1.);
hg3y->GetXaxis()->SetTitle("Number of clusters");
hg3y->GetYaxis()->SetTitle("Entries");
hg3y->GetXaxis()->SetTitleSize(0.04);
hg3y->GetYaxis()->SetTitleSize(0.04);
hg3y->GetXaxis()->SetNdivisions(6);
entries = hg3y->GetEntries();
if ( entries != 0)
	{scale = 100.0/entries;}
else
	{scale = 1;}
//hg3y->Scale(scale);
hg3y->Draw("");

gStyle->SetOptStat(1111);

string inputfile_str = string(inputfile);
size_t pos=inputfile_str.find("CRC-Run");
inputfile_str=inputfile_str.substr(pos+4);
string filename_nrCluster = "NumberOfClusters/NumberOfClusters_"+inputfile_str;
TFile* f2 = TFile::Open(filename_nrCluster.c_str(),"RECREATE");
hg1x->Write();
hg1y->Write();
hg2x->Write();
hg2y->Write();
hg3x->Write();
hg3y->Write();

f2->Write();
f2->Close();

file_outFileListNrCl << filename_nrCluster << " "; //filling the filelist

//==============================END:: Histograms of Number of cluster====================================================

}
