/*
 * 1. Make range external variable
 * 2. 
 */

#include <vector>
#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <fstream>
#include <TH1.h>
#include <TH2.h>
#include <TString.h>
#include <TAxis.h>
#include "doubleGausFit_withHistParameter.C"

void  AlignTrackers_Shift( string txtfilename, int RunNumber, double shi_g1xcl, double shi_g1ycl, double shi_g2xcl, double shi_g2ycl, double shi_g3xcl, double shi_g3ycl , double Trk1Pos, double Trk2Pos, double Trk3Pos){
    string thestring = "Position";
    //string txtfilename = thestring + ".txt";	// Input text file 
    cout<<"Input text file = "<< txtfilename <<endl;

    string shiftHead	= "shiftParameters_";
    string residualHead	= "residuals_";
    string ResidualRHead= "Residual_";

    string DirName = "Residual_XY_Trk_RootFile/";
    string DirNameShiftPar = "shiftParameters/";
    string DirNameResidual = "residual_txtFile/";

    char runname[50]; sprintf(runname,"_alignTrackers_R%i.txt",RunNumber);
    string foutname	= DirNameShiftPar+shiftHead+thestring+runname;	// Shift parameter will go in this text file
    string fout1name	= DirNameResidual+residualHead+thestring+runname;	// Residual will go into this

    fstream fin(txtfilename.c_str(),ios::in);
    if(!fin)	{cout<<"file not read"<<endl;}

    fstream fout(foutname.c_str(),ios::out);
    fstream fout1(fout1name.c_str(),ios::out);

    double Pos_g2xcl=0.0, Pos_g2ycl=0.0;
    double Pos_g3xcl=0.0, Pos_g3ycl=0.0;
    double Pos_g1xcl=0.0, Pos_g1ycl=0.0;
    std::vector<double> vPos_g2xcl; std::vector<double> vPos_g2ycl;
    std::vector<double> vPos_g3xcl; std::vector<double> vPos_g3ycl;
    std::vector<double> vPos_g1xcl; std::vector<double> vPos_g1ycl;
    
    bool verbose = 0;
    
    Int_t nbLines=0;
    //
    // Read all events and put each hits in a vector
    //
    while(fin>>Pos_g1xcl>>Pos_g1ycl>>Pos_g2xcl>>Pos_g2ycl>>Pos_g3xcl>>Pos_g3ycl){
	vPos_g2xcl.push_back(Pos_g2xcl); vPos_g2ycl.push_back(Pos_g2ycl); 
	vPos_g3xcl.push_back(Pos_g3xcl); vPos_g3ycl.push_back(Pos_g3ycl);
	vPos_g1xcl.push_back(Pos_g1xcl); vPos_g1ycl.push_back(Pos_g1ycl);
	nbLines++;
    } // getting input
    fin.close();
    //
    //	File read completed and file closed 
    //
    
    if (verbose)
	cout << "................................................"<<endl;
    
    
    double mean_g2xcl=0.0, mean_g2ycl=0.0;
    double mean_g3xcl=0.0, mean_g3ycl=0.0;
    double mean_g1xcl=0.0, mean_g1ycl=0.0;
    
    if (verbose)
	cout << "****************************************************"<<endl;
    
    Int_t iterNb=0;
    
    if (verbose)
	cout<<"Some problem 1"<<endl;
    
    double Tot_Shift_2X = 0.0, Tot_Shift_2Y = 0.0;
    double Tot_Shift_3X = 0.0, Tot_Shift_3Y = 0.0;

    fout<<"# shi_g1xcl"<<"\t"<<"shi_g1ycl"<<"\t"<<"shi_g2xcl"<<"\t"<<"shi_g2ycl"<<"\t"<<"shi_g3xcl"<<"\t"<<"shi_g3ycl"<<endl;
    while(1){
	iterNb++;
	if (verbose)
	    cout<<"Some problem 2"<<endl;
	char rootfile[50]; sprintf(rootfile,"_iter_%i_R%i.root",iterNb,RunNumber);
	string outputrootname=DirName+ResidualRHead+thestring+rootfile;
    cout<<"outputroot file name :  "<< outputrootname <<endl;
	TFile* f = new TFile(outputrootname.c_str(),"recreate");  
	cout <<"++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	char name1X[15];sprintf(name1X,"Pos_g1xcl_%i",iterNb); char name1Y[15];sprintf(name1Y,"Pos_g1xcl_%i",iterNb);
	char name2X[15];sprintf(name2X,"Pos_g2xcl_%i",iterNb); char name2Y[15];sprintf(name2Y,"Pos_g2ycl_%i",iterNb);
	char name3X[15];sprintf(name3X,"Pos_g3xcl_%i",iterNb); char name3Y[15];sprintf(name3Y,"Pos_g3ycl_%i",iterNb);
	
	if (verbose)
	    cout<<"Some problem 3"<<endl;
	TH1F* h_Pos_g1xcl = new TH1F(name1X,"",300,-60,60); h_Pos_g1xcl->SetXTitle("Cluster position [mm]"); h_Pos_g1xcl->SetYTitle("Frequency");h_Pos_g1xcl->SetLabelSize(0.045,"XY");h_Pos_g1xcl->SetTitleSize(0.045,"XY");
	TH1F* h_Pos_g1ycl = new TH1F(name1Y,"",300,-60,60); h_Pos_g1ycl->SetXTitle("Cluster position [mm]"); h_Pos_g1ycl->SetYTitle("Frequency");h_Pos_g1ycl->SetLabelSize(0.045,"XY");h_Pos_g1ycl->SetTitleSize(0.045,"XY");  
	TH1F* h_Pos_g2xcl = new TH1F(name2X,"",300,-60,60); h_Pos_g2xcl->SetXTitle("Cluster position [mm]"); h_Pos_g2xcl->SetYTitle("Frequency");h_Pos_g2xcl->SetLabelSize(0.045,"XY");h_Pos_g2xcl->SetTitleSize(0.045,"XY");
	TH1F* h_Pos_g2ycl = new TH1F(name2Y,"",300,-60,60); h_Pos_g2ycl->SetXTitle("Cluster position [mm]"); h_Pos_g2ycl->SetYTitle("Frequency");h_Pos_g2ycl->SetLabelSize(0.045,"XY");h_Pos_g2ycl->SetTitleSize(0.045,"XY");  
	TH1F* h_Pos_g3xcl = new TH1F(name3X,"",300,-60,60); h_Pos_g3xcl->SetXTitle("Cluster position [mm]"); h_Pos_g3xcl->SetYTitle("Frequency");h_Pos_g3xcl->SetLabelSize(0.045,"XY");h_Pos_g3xcl->SetTitleSize(0.045,"XY");
	TH1F* h_Pos_g3ycl = new TH1F(name3Y,"",300,-60,60); h_Pos_g3ycl->SetXTitle("Cluster position [mm]"); h_Pos_g3ycl->SetYTitle("Frequency");h_Pos_g3ycl->SetLabelSize(0.045,"XY");h_Pos_g3ycl->SetTitleSize(0.045,"XY");  

	
	if (verbose)
	    cout<<"Some problem 4"<<endl;
	char nameRes1X[30];sprintf(nameRes1X,"residual_g1xcl_%i",iterNb);char nameRes1Y[30];sprintf(nameRes1Y,"residual_g1ycl_%i",iterNb);
	char nameRes2X[30];sprintf(nameRes2X,"residual_g2xcl_%i",iterNb);char nameRes2Y[30];sprintf(nameRes2Y,"residual_g2ycl_%i",iterNb);
	char nameRes3X[30];sprintf(nameRes3X,"residual_g3xcl_%i",iterNb);char nameRes3Y[30];sprintf(nameRes3Y,"residual_g3ycl_%i",iterNb);
	
	TH1F* h_residual_g1xcl = new TH1F(nameRes1X,"",100,-2,2); h_residual_g1xcl->SetXTitle("Residual [mm]"); h_residual_g1xcl->SetYTitle("Frequency");h_residual_g1xcl->SetLabelSize(0.045,"XY");h_residual_g1xcl->SetTitleSize(0.045,"XY");
	TH1F* h_residual_g1ycl = new TH1F(nameRes1Y,"",100,-2,2); h_residual_g1ycl->SetXTitle("Residual [mm]"); h_residual_g1ycl->SetYTitle("Frequency");h_residual_g1ycl->SetLabelSize(0.045,"XY");h_residual_g1ycl->SetTitleSize(0.045,"XY");
	TH1F* h_residual_g2xcl = new TH1F(nameRes2X,"",100,-2,2); h_residual_g2xcl->SetXTitle("Residual [mm]"); h_residual_g2xcl->SetYTitle("Frequency");h_residual_g2xcl->SetLabelSize(0.045,"XY");h_residual_g2xcl->SetTitleSize(0.045,"XY");
	TH1F* h_residual_g2ycl = new TH1F(nameRes2Y,"",100,-2,2); h_residual_g2ycl->SetXTitle("Residual [mm]"); h_residual_g2ycl->SetYTitle("Frequency");h_residual_g2ycl->SetLabelSize(0.045,"XY");h_residual_g2ycl->SetTitleSize(0.045,"XY");
	TH1F* h_residual_g3xcl = new TH1F(nameRes3X,"",100,-2,2); h_residual_g3xcl->SetXTitle("Residual [mm]"); h_residual_g3xcl->SetYTitle("Frequency");h_residual_g3xcl->SetLabelSize(0.045,"XY");h_residual_g3xcl->SetTitleSize(0.045,"XY");
	TH1F* h_residual_g3ycl = new TH1F(nameRes3Y,"",100,-2,2); h_residual_g3ycl->SetXTitle("Residual [mm]"); h_residual_g3ycl->SetYTitle("Frequency");h_residual_g3ycl->SetLabelSize(0.045,"XY");h_residual_g3ycl->SetTitleSize(0.045,"XY");

	// Print the mean position of each Detector
	fout<<shi_g1xcl<<"\t"<<shi_g1ycl<<"\t"<<shi_g2xcl<<"\t"<<shi_g2ycl<<"\t"<<shi_g3xcl<<"\t"<<shi_g3ycl<<"\t"<<endl;
	if (verbose)
	    cout<<"Some problem 5"<<endl;
	
	
	int nnnn=0;
	
	
	if (verbose)
	    cout<<"Some problem 6"<<endl;
	
	for(unsigned int i=0;i<vPos_g1xcl.size();i++){

	    TGraph* g1 = new TGraph();
	    TF1* f1 = new TF1("line1","[0]+[1]*x",0,900);
	    TGraph* g2 = new TGraph();
	    TF1* f2 = new TF1("line2","[0]+[1]*x",0,900);

	    
	    //cout<<"===========> "<<shi_g1xcl<<"\t"<<shi_g1ycl<<endl;
	    vPos_g1xcl[i] = vPos_g1xcl[i] - shi_g1xcl; vPos_g1ycl[i] = vPos_g1ycl[i] - shi_g1ycl;
	    vPos_g2xcl[i] = vPos_g2xcl[i] - shi_g2xcl; vPos_g2ycl[i] = vPos_g2ycl[i] - shi_g2ycl;      
	    vPos_g3xcl[i] = vPos_g3xcl[i] - shi_g3xcl; vPos_g3ycl[i] = vPos_g3ycl[i] - shi_g3ycl;
	    
	    h_Pos_g1xcl->Fill(vPos_g1xcl[i]); h_Pos_g1ycl->Fill(vPos_g1ycl[i]);
	    h_Pos_g2xcl->Fill(vPos_g2xcl[i]); h_Pos_g2ycl->Fill(vPos_g2ycl[i]);
	    h_Pos_g3xcl->Fill(vPos_g3xcl[i]); h_Pos_g3ycl->Fill(vPos_g3ycl[i]);

	    if (verbose)
		cout<<"Some problem 7"<<endl;
	    
	    
	    g1->SetPoint(0, Trk1Pos, vPos_g1xcl[i]);
	    g1->SetPoint(1, Trk2Pos, vPos_g2xcl[i]);
	    g1->SetPoint(2, Trk3Pos, vPos_g3xcl[i]);
	    
	    if (verbose)
		cout<<"vPos_g1xcl["<<i<<"] = "<<vPos_g1xcl[i]<<"\tvPos_g2xcl["<<i<<"] = "<<vPos_g2xcl[i]<<"\tvPos_g3xcl["<<i<<"] = "<<vPos_g3xcl[i]<<endl;
	    
	    g1->Fit("line1","Q");
	    
	    double intercept1 = f1->GetParameter(0);
	    double slope1     = f1->GetParameter(1);
	    double Measured_g1xcl = intercept1 + slope1*Trk1Pos;
	    //double Measured_g1xcl = vPos_g1xcl[i];		// Reference Tracker position should not be changed.
	    double Measured_g2xcl = intercept1 + slope1*Trk2Pos;
	    double Measured_g3xcl = intercept1 + slope1*Trk3Pos;
	    
	    if (verbose)
		cout<<"intercept1 = "<<intercept1<<"\tslope1 = "<<slope1 <<endl;
	    
	    
	    h_residual_g1xcl->Fill(Measured_g1xcl-vPos_g1xcl[i]);
	    h_residual_g2xcl->Fill(Measured_g2xcl-vPos_g2xcl[i]);
	    h_residual_g3xcl->Fill(Measured_g3xcl-vPos_g3xcl[i]);

	    if (verbose)
		cout<<"Measured_g1xcl = "<<Measured_g1xcl<<"\t vPos_g2xcl = "<<vPos_g2xcl[i]<<"\tDifference = "<<Measured_g2xcl-vPos_g2xcl[i]<<endl;
	    delete f1; delete g1;
	    
	    if (verbose)
		cout<<"Some problem 8"<<endl;
	    
	    g2->SetPoint(0,Trk1Pos,vPos_g1ycl[i]);
	    g2->SetPoint(1,Trk2Pos,vPos_g2ycl[i]);
	    g2->SetPoint(2,Trk3Pos,vPos_g3ycl[i]);
	    
	    // inclusive
	    
	    g2->Fit("line2","Q");
	    double intercept2 = f2->GetParameter(0);
	    double slope2     = f2->GetParameter(1);
	    double Measured_g1ycl = intercept2 + slope2*Trk1Pos;
	    //double Measured_g1ycl = vPos_g1ycl[i];	// Reference Tracker position should not be changed.
	    double Measured_g2ycl = intercept2 + slope2*Trk2Pos;
	    double Measured_g3ycl = intercept2 + slope2*Trk3Pos;
	    
	    if (verbose)
		cout<<"Some problem 9"<<endl;

	    h_residual_g1ycl->Fill(Measured_g1ycl-vPos_g1ycl[i]);
	    h_residual_g2ycl->Fill(Measured_g2ycl-vPos_g2ycl[i]);
	    h_residual_g3ycl->Fill(Measured_g3ycl-vPos_g3ycl[i]);
	    
	    delete f2; delete g2;
	    
	    if (verbose)
		cout<<"Some problem 11"<<endl;
	    
	    nnnn++;
	    
	}//for loop g2xcl size
	
	gStyle->SetOptFit(1111);
	
	if (verbose)
	    cout<<"Some problem 13"<<endl;
	
	I2GFvalues myValues;

	myValues = I2GFmainLoop(h_residual_g1xcl,1,10,1);
	mean_g1xcl = myValues.mean; //

	myValues = I2GFmainLoop(h_residual_g1ycl,1,10,1);
	mean_g1ycl = myValues.mean;

	myValues = I2GFmainLoop(h_residual_g2xcl,1,10,1);
	mean_g2xcl = myValues.mean; //sigmaEta5=myValues.sigma;

	myValues = I2GFmainLoop(h_residual_g2ycl,1,10,1);
	mean_g2ycl = myValues.mean; //

	myValues = I2GFmainLoop(h_residual_g3xcl,1,10,1);
	mean_g3xcl = myValues.mean; //

	myValues = I2GFmainLoop(h_residual_g3ycl,1,10,1);
	mean_g3ycl = myValues.mean;
	
	
	cout<<"residual mean: "<<mean_g1xcl<<"\t"<<mean_g1ycl<<"\t"<<mean_g2xcl<<"\t"<<mean_g2ycl<<"\t"<<mean_g3xcl<<"\t"<<mean_g3ycl<<endl;
	
	fout1<<"residual mean: "<<mean_g1xcl<<"\t"<<mean_g1ycl<<"\t"<<mean_g2xcl<<"\t"<<mean_g2ycl<<"\t"<<mean_g3xcl<<"\t"<<mean_g3ycl<<endl;
	
	f->Write();
	f->Close();
	
	double factor = -0.1;
	
	//shi_g1xcl = mean_g1xcl*factor; shi_g1ycl = mean_g1ycl*factor; 
	shi_g1xcl = 0.0; shi_g1ycl = 0.0; 
	shi_g2xcl = mean_g2xcl*factor; shi_g2ycl = mean_g2ycl*factor; 
	shi_g3xcl = mean_g3xcl*factor; shi_g3ycl = mean_g3ycl*factor; 
    cout<<"shi_g2xcl = "<<shi_g2xcl <<"\tshi_g3xcl = "<<shi_g3xcl<<endl;	

	Tot_Shift_2X +=shi_g2xcl;
	Tot_Shift_2Y +=shi_g2ycl;
	Tot_Shift_3X +=shi_g3xcl;
	Tot_Shift_3Y +=shi_g3ycl;
	
	
	//	if((mean_g1xcl>=-0.005 && mean_g1xcl<=0.005) && (mean_g1ycl>=-0.005 && mean_g1ycl<=0.005))
	if((mean_g2xcl>=-0.005 && mean_g2xcl<=0.005) && (mean_g2ycl>=-0.005 && mean_g2ycl<=0.005))
	    if((mean_g3xcl>=-0.005 && mean_g3xcl<=0.005) && (mean_g3ycl>=-0.005 && mean_g3ycl<=0.005))
		{
		    cout<<"find it...iterating "<<iterNb<<" times."<<endl;
		    break;
		}
	//h_residual_g2xcl->Reset();
	//h_residual_g1xcl->Reset();
	//h_residual_g3xcl->Reset();
	
	if(iterNb>500) break;
	
	cout<<"iterating "<<iterNb<<" time done."<<endl;
    }//while(1)

    cout<<"Shift in 2X = "<<Tot_Shift_2X<<endl; 
    cout<<"Shift in 2Y = "<<Tot_Shift_2Y<<endl; 
    cout<<"Shift in 3X = "<<Tot_Shift_3X<<endl; 
    cout<<"Shift in 3Y = "<<Tot_Shift_3Y<<endl; 
    fout.close();
    fout1.close();
    // return 0;
} // entire script
