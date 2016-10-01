/*
#include "TROOT.h" 
#include "TTree.h" 

#include "TChain.h" 
#include "TBranch.h" 
*/

// Reads the content of folder NumberOfClusters and creates plots Nr.Clusters vs HV
// for each detector (g1x, g1y, g2x, g2y, g3x, g3y).
// Filenames (rootfiles) to be processed need to be chosen by hand (in "if" conditions)
// For each processed rootfile: HV, current, choice between H2/H4 testbeam need to be manually written.


#include "TApplication.h"
#include <TFile.h>
#include "TH1F.h"
#include "TH2F.h"
#include "TString.h"
#include "TCanvas.h"
#include "TGraph.h" 
#include "TLegend.h"
#include "TStyle.h"
#include "TPaveLabel.h"

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

TApplication *myapp=new TApplication("myapp",0,0);

	int verbose = 1;
	//int VFATscheme = 5; //choose which VFATscheme to be plotted for H4 data

	//voltages
	vector<double> x_mu_H2;
	vector<double> x_pi_H2;
	vector<double> x_mu_H4;
	vector<double> x_pi_H4;
	//currents
	vector<double> curr_mu_H2;
	vector<double> curr_pi_H2;
	vector<double> curr_mu_H4;
	vector<double> curr_pi_H4;

	//========================================start: initialization of percent vectors=============================================================================================
	//==========================================percent for H2 runs==============================================================================================================
	//with 0 Clusters
	vector<double> g1x_y0_mu_H2;vector<double> g1y_y0_mu_H2;vector<double> g2x_y0_mu_H2;vector<double> g2y_y0_mu_H2;vector<double> g3x_y0_mu_H2;vector<double> g3y_y0_mu_H2; 
	vector<double> g1x_y0_pi_H2;vector<double> g1y_y0_pi_H2;vector<double> g2x_y0_pi_H2;vector<double> g2y_y0_pi_H2;vector<double> g3x_y0_pi_H2;vector<double> g3y_y0_pi_H2; 
	//with 1 Cluster
	vector<double> g1x_y1_mu_H2;vector<double> g1y_y1_mu_H2;vector<double> g2x_y1_mu_H2;vector<double> g2y_y1_mu_H2;vector<double> g3x_y1_mu_H2;vector<double> g3y_y1_mu_H2; 
	vector<double> g1x_y1_pi_H2;vector<double> g1y_y1_pi_H2;vector<double> g2x_y1_pi_H2;vector<double> g2y_y1_pi_H2;vector<double> g3x_y1_pi_H2;vector<double> g3y_y1_pi_H2; 
	//with 2 Cluster
	vector<double> g1x_y2_mu_H2;vector<double> g1y_y2_mu_H2;vector<double> g2x_y2_mu_H2;vector<double> g2y_y2_mu_H2;vector<double> g3x_y2_mu_H2;vector<double> g3y_y2_mu_H2; 
	vector<double> g1x_y2_pi_H2;vector<double> g1y_y2_pi_H2;vector<double> g2x_y2_pi_H2;vector<double> g2y_y2_pi_H2;vector<double> g3x_y2_pi_H2;vector<double> g3y_y2_pi_H2; 
	//with 3 Cluster
	vector<double> g1x_y3_mu_H2;vector<double> g1y_y3_mu_H2;vector<double> g2x_y3_mu_H2;vector<double> g2y_y3_mu_H2;vector<double> g3x_y3_mu_H2;vector<double> g3y_y3_mu_H2; 
	vector<double> g1x_y3_pi_H2;vector<double> g1y_y3_pi_H2;vector<double> g2x_y3_pi_H2;vector<double> g2y_y3_pi_H2;vector<double> g3x_y3_pi_H2;vector<double> g3y_y3_pi_H2; 	
	//with 4 Cluster
	vector<double> g1x_y4_mu_H2;vector<double> g1y_y4_mu_H2;vector<double> g2x_y4_mu_H2;vector<double> g2y_y4_mu_H2;vector<double> g3x_y4_mu_H2;vector<double> g3y_y4_mu_H2; 
	vector<double> g1x_y4_pi_H2;vector<double> g1y_y4_pi_H2;vector<double> g2x_y4_pi_H2;vector<double> g2y_y4_pi_H2;vector<double> g3x_y4_pi_H2;vector<double> g3y_y4_pi_H2; 
	//with 5 Cluster
	vector<double> g1x_y5_mu_H2;vector<double> g1y_y5_mu_H2;vector<double> g2x_y5_mu_H2;vector<double> g2y_y5_mu_H2;vector<double> g3x_y5_mu_H2;vector<double> g3y_y5_mu_H2; 
	vector<double> g1x_y5_pi_H2;vector<double> g1y_y5_pi_H2;vector<double> g2x_y5_pi_H2;vector<double> g2y_y5_pi_H2;vector<double> g3x_y5_pi_H2;vector<double> g3y_y5_pi_H2; 

	//==========================================percent for H4 runs==============================================================================================================
	//with 0 Clusters
	vector<double> g1x_y0_mu_H4;vector<double> g1y_y0_mu_H4;vector<double> g2x_y0_mu_H4;vector<double> g2y_y0_mu_H4;vector<double> g3x_y0_mu_H4;vector<double> g3y_y0_mu_H4; 
	vector<double> g1x_y0_pi_H4;vector<double> g1y_y0_pi_H4;vector<double> g2x_y0_pi_H4;vector<double> g2y_y0_pi_H4;vector<double> g3x_y0_pi_H4;vector<double> g3y_y0_pi_H4; 
	//with 1 Cluster
	vector<double> g1x_y1_mu_H4;vector<double> g1y_y1_mu_H4;vector<double> g2x_y1_mu_H4;vector<double> g2y_y1_mu_H4;vector<double> g3x_y1_mu_H4;vector<double> g3y_y1_mu_H4; 
	vector<double> g1x_y1_pi_H4;vector<double> g1y_y1_pi_H4;vector<double> g2x_y1_pi_H4;vector<double> g2y_y1_pi_H4;vector<double> g3x_y1_pi_H4;vector<double> g3y_y1_pi_H4; 
	//with 2 Cluster
	vector<double> g1x_y2_mu_H4;vector<double> g1y_y2_mu_H4;vector<double> g2x_y2_mu_H4;vector<double> g2y_y2_mu_H4;vector<double> g3x_y2_mu_H4;vector<double> g3y_y2_mu_H4; 
	vector<double> g1x_y2_pi_H4;vector<double> g1y_y2_pi_H4;vector<double> g2x_y2_pi_H4;vector<double> g2y_y2_pi_H4;vector<double> g3x_y2_pi_H4;vector<double> g3y_y2_pi_H4; 
	//with 3 Cluster
	vector<double> g1x_y3_mu_H4;vector<double> g1y_y3_mu_H4;vector<double> g2x_y3_mu_H4;vector<double> g2y_y3_mu_H4;vector<double> g3x_y3_mu_H4;vector<double> g3y_y3_mu_H4; 
	vector<double> g1x_y3_pi_H4;vector<double> g1y_y3_pi_H4;vector<double> g2x_y3_pi_H4;vector<double> g2y_y3_pi_H4;vector<double> g3x_y3_pi_H4;vector<double> g3y_y3_pi_H4; 	
	//with 4 Cluster
	vector<double> g1x_y4_mu_H4;vector<double> g1y_y4_mu_H4;vector<double> g2x_y4_mu_H4;vector<double> g2y_y4_mu_H4;vector<double> g3x_y4_mu_H4;vector<double> g3y_y4_mu_H4; 
	vector<double> g1x_y4_pi_H4;vector<double> g1y_y4_pi_H4;vector<double> g2x_y4_pi_H4;vector<double> g2y_y4_pi_H4;vector<double> g3x_y4_pi_H4;vector<double> g3y_y4_pi_H4; 
	//with 5 Cluster
	vector<double> g1x_y5_mu_H4;vector<double> g1y_y5_mu_H4;vector<double> g2x_y5_mu_H4;vector<double> g2y_y5_mu_H4;vector<double> g3x_y5_mu_H4;vector<double> g3y_y5_mu_H4; 
	vector<double> g1x_y5_pi_H4;vector<double> g1y_y5_pi_H4;vector<double> g2x_y5_pi_H4;vector<double> g2y_y5_pi_H4;vector<double> g3x_y5_pi_H4;vector<double> g3y_y5_pi_H4; 
	//========================================end: initialization of percent vectors=============================================================================================

int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL)
    	{
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    	}

    while ((dirp = readdir(dp)) != NULL)
    	{
        files.push_back(string(dirp->d_name));
    	}
    closedir(dp);
    return 0;
}

int process_muH2 (string files)
{
	        string rootfile= "NumberOfClusters/";
        	rootfile = rootfile.append(files) ;
        	TFile* f = TFile::Open(rootfile.c_str(), "READ");
        	//if->ls();

        	TH1F * hg1x = (TH1F*)f->Get("Number of clusters on g1x;2");
			TH1F * hg1y = (TH1F*)f->Get("Number of clusters on g1y;2");
			TH1F * hg2x = (TH1F*)f->Get("Number of clusters on g2x;2");
			TH1F * hg2y = (TH1F*)f->Get("Number of clusters on g2y;2");
			TH1F * hg3x = (TH1F*)f->Get("Number of clusters on g3x;2");
			TH1F * hg3y = (TH1F*)f->Get("Number of clusters on g3y;2");

			//================read data from hg1x======================
			double g1x_nrCl0 = hg1x->GetBinContent(1);
			double g1x_nrCl1 = hg1x->GetBinContent(2);
			double g1x_nrCl2 = hg1x->GetBinContent(3);
			double g1x_nrCl3 = hg1x->GetBinContent(4);
			double g1x_nrCl4 = hg1x->GetBinContent(5);
			double g1x_nrCl5 = hg1x->GetBinContent(6);

			if (verbose) cout << files << ": " << g1x_nrCl0 << ", " << g1x_nrCl1 << ", " << g1x_nrCl2 << ", " << g1x_nrCl3 << ", " << g1x_nrCl4 << ", " << g1x_nrCl5 << endl;
        	
        	g1x_y0_mu_H2.push_back(g1x_nrCl0);
        	g1x_y1_mu_H2.push_back(g1x_nrCl1);
        	g1x_y2_mu_H2.push_back(g1x_nrCl2);
        	g1x_y3_mu_H2.push_back(g1x_nrCl3);
        	g1x_y4_mu_H2.push_back(g1x_nrCl4);
        	g1x_y5_mu_H2.push_back(g1x_nrCl5);

        	//================read data from hg2x======================
			double g2x_nrCl0 = hg2x->GetBinContent(1);
			double g2x_nrCl1 = hg2x->GetBinContent(2);
			double g2x_nrCl2 = hg2x->GetBinContent(3);
			double g2x_nrCl3 = hg2x->GetBinContent(4);
			double g2x_nrCl4 = hg2x->GetBinContent(5);
			double g2x_nrCl5 = hg2x->GetBinContent(6);

			if (verbose) cout << files << ": " << g2x_nrCl0 << ", " << g2x_nrCl1 << ", " << g2x_nrCl2 << ", " << g2x_nrCl3 << ", " << g2x_nrCl4 << ", " << g2x_nrCl5 << endl;
        	
        	g2x_y0_mu_H2.push_back(g2x_nrCl0);
        	g2x_y1_mu_H2.push_back(g2x_nrCl1);
        	g2x_y2_mu_H2.push_back(g2x_nrCl2);
        	g2x_y3_mu_H2.push_back(g2x_nrCl3);
        	g2x_y4_mu_H2.push_back(g2x_nrCl4);
        	g2x_y5_mu_H2.push_back(g2x_nrCl5);


        	//================read data from hg3x======================
			double g3x_nrCl0 = hg3x->GetBinContent(1);
			double g3x_nrCl1 = hg3x->GetBinContent(2);
			double g3x_nrCl2 = hg3x->GetBinContent(3);
			double g3x_nrCl3 = hg3x->GetBinContent(4);
			double g3x_nrCl4 = hg3x->GetBinContent(5);
			double g3x_nrCl5 = hg3x->GetBinContent(6);

			if (verbose) cout << files << ": " << g3x_nrCl0 << ", " << g3x_nrCl1 << ", " << g3x_nrCl2 << ", " << g3x_nrCl3 << ", " << g3x_nrCl4 << ", " << g3x_nrCl5 << endl;
        	
        	g3x_y0_mu_H2.push_back(g3x_nrCl0);
        	g3x_y1_mu_H2.push_back(g3x_nrCl1);
        	g3x_y2_mu_H2.push_back(g3x_nrCl2);
        	g3x_y3_mu_H2.push_back(g3x_nrCl3);
        	g3x_y4_mu_H2.push_back(g3x_nrCl4);
        	g3x_y5_mu_H2.push_back(g3x_nrCl5);

        	//================read data from hg1y======================
			double g1y_nrCl0 = hg1y->GetBinContent(1);
			double g1y_nrCl1 = hg1y->GetBinContent(2);
			double g1y_nrCl2 = hg1y->GetBinContent(3);
			double g1y_nrCl3 = hg1y->GetBinContent(4);
			double g1y_nrCl4 = hg1y->GetBinContent(5);
			double g1y_nrCl5 = hg1y->GetBinContent(6);

			if (verbose) cout << files << ": " << g1y_nrCl0 << ", " << g1y_nrCl1 << ", " << g1y_nrCl2 << ", " << g1y_nrCl3 << ", " << g1y_nrCl4 << ", " << g1y_nrCl5 << endl;
        	
        	g1y_y0_mu_H2.push_back(g1y_nrCl0);
        	g1y_y1_mu_H2.push_back(g1y_nrCl1);
        	g1y_y2_mu_H2.push_back(g1y_nrCl2);
        	g1y_y3_mu_H2.push_back(g1y_nrCl3);
        	g1y_y4_mu_H2.push_back(g1y_nrCl4);
        	g1y_y5_mu_H2.push_back(g1y_nrCl5);

        	//================read data from hg2y======================
			double g2y_nrCl0 = hg2y->GetBinContent(1);
			double g2y_nrCl1 = hg2y->GetBinContent(2);
			double g2y_nrCl2 = hg2y->GetBinContent(3);
			double g2y_nrCl3 = hg2y->GetBinContent(4);
			double g2y_nrCl4 = hg2y->GetBinContent(5);
			double g2y_nrCl5 = hg2y->GetBinContent(6);

			if (verbose) cout << files << ": " << g2y_nrCl0 << ", " << g2y_nrCl1 << ", " << g2y_nrCl2 << ", " << g2y_nrCl3 << ", " << g2y_nrCl4 << ", " << g2y_nrCl5 << endl;
        	
        	g2y_y0_mu_H2.push_back(g2y_nrCl0);
        	g2y_y1_mu_H2.push_back(g2y_nrCl1);
        	g2y_y2_mu_H2.push_back(g2y_nrCl2);
        	g2y_y3_mu_H2.push_back(g2y_nrCl3);
        	g2y_y4_mu_H2.push_back(g2y_nrCl4);
        	g2y_y5_mu_H2.push_back(g2y_nrCl5);

        	//================read data from hg3y======================
			double g3y_nrCl0 = hg3y->GetBinContent(1);
			double g3y_nrCl1 = hg3y->GetBinContent(2);
			double g3y_nrCl2 = hg3y->GetBinContent(3);
			double g3y_nrCl3 = hg3y->GetBinContent(4);
			double g3y_nrCl4 = hg3y->GetBinContent(5);
			double g3y_nrCl5 = hg3y->GetBinContent(6);

			if (verbose) cout << files << ": " << g3y_nrCl0 << ", " << g3y_nrCl1 << ", " << g3y_nrCl2 << ", " << g3y_nrCl3 << ", " << g3y_nrCl4 << ", " << g3y_nrCl5 << endl;
        	
        	g3y_y0_mu_H2.push_back(g3y_nrCl0);
        	g3y_y1_mu_H2.push_back(g3y_nrCl1);
        	g3y_y2_mu_H2.push_back(g3y_nrCl2);
        	g3y_y3_mu_H2.push_back(g3y_nrCl3);
        	g3y_y4_mu_H2.push_back(g3y_nrCl4);
        	g3y_y5_mu_H2.push_back(g3y_nrCl5);


        	f->Close();
        	return 0;
}


int process_piH2 (string files)
{
	        string rootfile= "NumberOfClusters/";
        	rootfile = rootfile.append(files) ;
        	TFile* f = TFile::Open(rootfile.c_str(), "READ");
        	//f->ls();

        	TH1F * hg1x = (TH1F*)f->Get("Number of clusters on g1x;2");
			TH1F * hg1y = (TH1F*)f->Get("Number of clusters on g1y;2");
			TH1F * hg2x = (TH1F*)f->Get("Number of clusters on g2x;2");
			TH1F * hg2y = (TH1F*)f->Get("Number of clusters on g2y;2");
			TH1F * hg3x = (TH1F*)f->Get("Number of clusters on g3x;2");
			TH1F * hg3y = (TH1F*)f->Get("Number of clusters on g3y;2");

			//================read data from hg1x======================
			double g1x_nrCl0 = hg1x->GetBinContent(1);
			double g1x_nrCl1 = hg1x->GetBinContent(2);
			double g1x_nrCl2 = hg1x->GetBinContent(3);
			double g1x_nrCl3 = hg1x->GetBinContent(4);
			double g1x_nrCl4 = hg1x->GetBinContent(5);
			double g1x_nrCl5 = hg1x->GetBinContent(6);

			if (verbose) cout << files << ": " << g1x_nrCl0 << ", " << g1x_nrCl1 << ", " << g1x_nrCl2 << ", " << g1x_nrCl3 << ", " << g1x_nrCl4 << ", " << g1x_nrCl5 << endl;
        	
        	g1x_y0_pi_H2.push_back(g1x_nrCl0);
        	g1x_y1_pi_H2.push_back(g1x_nrCl1);
        	g1x_y2_pi_H2.push_back(g1x_nrCl2);
        	g1x_y3_pi_H2.push_back(g1x_nrCl3);
        	g1x_y4_pi_H2.push_back(g1x_nrCl4);
        	g1x_y5_pi_H2.push_back(g1x_nrCl5);

        	//================read data from hg2x======================
			double g2x_nrCl0 = hg2x->GetBinContent(1);
			double g2x_nrCl1 = hg2x->GetBinContent(2);
			double g2x_nrCl2 = hg2x->GetBinContent(3);
			double g2x_nrCl3 = hg2x->GetBinContent(4);
			double g2x_nrCl4 = hg2x->GetBinContent(5);
			double g2x_nrCl5 = hg2x->GetBinContent(6);

			if (verbose) cout << files << ": " << g2x_nrCl0 << ", " << g2x_nrCl1 << ", " << g2x_nrCl2 << ", " << g2x_nrCl3 << ", " << g2x_nrCl4 << ", " << g2x_nrCl5 << endl;
        	
        	g2x_y0_pi_H2.push_back(g2x_nrCl0);
        	g2x_y1_pi_H2.push_back(g2x_nrCl1);
        	g2x_y2_pi_H2.push_back(g2x_nrCl2);
        	g2x_y3_pi_H2.push_back(g2x_nrCl3);
        	g2x_y4_pi_H2.push_back(g2x_nrCl4);
        	g2x_y5_pi_H2.push_back(g2x_nrCl5);


        	//================read data from hg3x======================
			double g3x_nrCl0 = hg3x->GetBinContent(1);
			double g3x_nrCl1 = hg3x->GetBinContent(2);
			double g3x_nrCl2 = hg3x->GetBinContent(3);
			double g3x_nrCl3 = hg3x->GetBinContent(4);
			double g3x_nrCl4 = hg3x->GetBinContent(5);
			double g3x_nrCl5 = hg3x->GetBinContent(6);

			if (verbose) cout << files << ": " << g3x_nrCl0 << ", " << g3x_nrCl1 << ", " << g3x_nrCl2 << ", " << g3x_nrCl3 << ", " << g3x_nrCl4 << ", " << g3x_nrCl5 << endl;
        	
        	g3x_y0_pi_H2.push_back(g3x_nrCl0);
        	g3x_y1_pi_H2.push_back(g3x_nrCl1);
        	g3x_y2_pi_H2.push_back(g3x_nrCl2);
        	g3x_y3_pi_H2.push_back(g3x_nrCl3);
        	g3x_y4_pi_H2.push_back(g3x_nrCl4);
        	g3x_y5_pi_H2.push_back(g3x_nrCl5);

        	//================read data from hg1y======================
			double g1y_nrCl0 = hg1y->GetBinContent(1);
			double g1y_nrCl1 = hg1y->GetBinContent(2);
			double g1y_nrCl2 = hg1y->GetBinContent(3);
			double g1y_nrCl3 = hg1y->GetBinContent(4);
			double g1y_nrCl4 = hg1y->GetBinContent(5);
			double g1y_nrCl5 = hg1y->GetBinContent(6);

			if (verbose) cout << files << ": " << g1y_nrCl0 << ", " << g1y_nrCl1 << ", " << g1y_nrCl2 << ", " << g1y_nrCl3 << ", " << g1y_nrCl4 << ", " << g1y_nrCl5 << endl;
        	
        	g1y_y0_pi_H2.push_back(g1y_nrCl0);
        	g1y_y1_pi_H2.push_back(g1y_nrCl1);
        	g1y_y2_pi_H2.push_back(g1y_nrCl2);
        	g1y_y3_pi_H2.push_back(g1y_nrCl3);
        	g1y_y4_pi_H2.push_back(g1y_nrCl4);
        	g1y_y5_pi_H2.push_back(g1y_nrCl5);

        	//================read data from hg2y======================
			double g2y_nrCl0 = hg2y->GetBinContent(1);
			double g2y_nrCl1 = hg2y->GetBinContent(2);
			double g2y_nrCl2 = hg2y->GetBinContent(3);
			double g2y_nrCl3 = hg2y->GetBinContent(4);
			double g2y_nrCl4 = hg2y->GetBinContent(5);
			double g2y_nrCl5 = hg2y->GetBinContent(6);

			if (verbose) cout << files << ": " << g2y_nrCl0 << ", " << g2y_nrCl1 << ", " << g2y_nrCl2 << ", " << g2y_nrCl3 << ", " << g2y_nrCl4 << ", " << g2y_nrCl5 << endl;
        	
        	g2y_y0_pi_H2.push_back(g2y_nrCl0);
        	g2y_y1_pi_H2.push_back(g2y_nrCl1);
        	g2y_y2_pi_H2.push_back(g2y_nrCl2);
        	g2y_y3_pi_H2.push_back(g2y_nrCl3);
        	g2y_y4_pi_H2.push_back(g2y_nrCl4);
        	g2y_y5_pi_H2.push_back(g2y_nrCl5);

        	//================read data from hg3y======================
			double g3y_nrCl0 = hg3y->GetBinContent(1);
			double g3y_nrCl1 = hg3y->GetBinContent(2);
			double g3y_nrCl2 = hg3y->GetBinContent(3);
			double g3y_nrCl3 = hg3y->GetBinContent(4);
			double g3y_nrCl4 = hg3y->GetBinContent(5);
			double g3y_nrCl5 = hg3y->GetBinContent(6);

			if (verbose) cout << files << ": " << g3y_nrCl0 << ", " << g3y_nrCl1 << ", " << g3y_nrCl2 << ", " << g3y_nrCl3 << ", " << g3y_nrCl4 << ", " << g3y_nrCl5 << endl;
        	
        	g3y_y0_pi_H2.push_back(g3y_nrCl0);
        	g3y_y1_pi_H2.push_back(g3y_nrCl1);
        	g3y_y2_pi_H2.push_back(g3y_nrCl2);
        	g3y_y3_pi_H2.push_back(g3y_nrCl3);
        	g3y_y4_pi_H2.push_back(g3y_nrCl4);
        	g3y_y5_pi_H2.push_back(g3y_nrCl5);


        	f->Close();
        	return 0;
}


int process_muH4 (string files)
{
	        string rootfile= "NumberOfClusters/";
        	rootfile = rootfile.append(files) ;
        	TFile* f = TFile::Open(rootfile.c_str(), "READ");
        	//if->ls();

        	TH1F * hg1x = (TH1F*)f->Get("Number of clusters on g1x;2");
			TH1F * hg1y = (TH1F*)f->Get("Number of clusters on g1y;2");
			TH1F * hg2x = (TH1F*)f->Get("Number of clusters on g2x;2");
			TH1F * hg2y = (TH1F*)f->Get("Number of clusters on g2y;2");
			TH1F * hg3x = (TH1F*)f->Get("Number of clusters on g3x;2");
			TH1F * hg3y = (TH1F*)f->Get("Number of clusters on g3y;2");

			//================read data from hg1x======================
			double g1x_nrCl0 = hg1x->GetBinContent(1);
			double g1x_nrCl1 = hg1x->GetBinContent(2);
			double g1x_nrCl2 = hg1x->GetBinContent(3);
			double g1x_nrCl3 = hg1x->GetBinContent(4);
			double g1x_nrCl4 = hg1x->GetBinContent(5);
			double g1x_nrCl5 = hg1x->GetBinContent(6);

			if (verbose) cout << files << ": " << g1x_nrCl0 << ", " << g1x_nrCl1 << ", " << g1x_nrCl2 << ", " << g1x_nrCl3 << ", " << g1x_nrCl4 << ", " << g1x_nrCl5 << endl;
        	
        	g1x_y0_mu_H4.push_back(g1x_nrCl0);
        	g1x_y1_mu_H4.push_back(g1x_nrCl1);
        	g1x_y2_mu_H4.push_back(g1x_nrCl2);
        	g1x_y3_mu_H4.push_back(g1x_nrCl3);
        	g1x_y4_mu_H4.push_back(g1x_nrCl4);
        	g1x_y5_mu_H4.push_back(g1x_nrCl5);

        	//================read data from hg2x======================
			double g2x_nrCl0 = hg2x->GetBinContent(1);
			double g2x_nrCl1 = hg2x->GetBinContent(2);
			double g2x_nrCl2 = hg2x->GetBinContent(3);
			double g2x_nrCl3 = hg2x->GetBinContent(4);
			double g2x_nrCl4 = hg2x->GetBinContent(5);
			double g2x_nrCl5 = hg2x->GetBinContent(6);

			if (verbose) cout << files << ": " << g2x_nrCl0 << ", " << g2x_nrCl1 << ", " << g2x_nrCl2 << ", " << g2x_nrCl3 << ", " << g2x_nrCl4 << ", " << g2x_nrCl5 << endl;
        	
        	g2x_y0_mu_H4.push_back(g2x_nrCl0);
        	g2x_y1_mu_H4.push_back(g2x_nrCl1);
        	g2x_y2_mu_H4.push_back(g2x_nrCl2);
        	g2x_y3_mu_H4.push_back(g2x_nrCl3);
        	g2x_y4_mu_H4.push_back(g2x_nrCl4);
        	g2x_y5_mu_H4.push_back(g2x_nrCl5);


        	//================read data from hg3x======================
			double g3x_nrCl0 = hg3x->GetBinContent(1);
			double g3x_nrCl1 = hg3x->GetBinContent(2);
			double g3x_nrCl2 = hg3x->GetBinContent(3);
			double g3x_nrCl3 = hg3x->GetBinContent(4);
			double g3x_nrCl4 = hg3x->GetBinContent(5);
			double g3x_nrCl5 = hg3x->GetBinContent(6);

			if (verbose) cout << files << ": " << g3x_nrCl0 << ", " << g3x_nrCl1 << ", " << g3x_nrCl2 << ", " << g3x_nrCl3 << ", " << g3x_nrCl4 << ", " << g3x_nrCl5 << endl;
        	
        	g3x_y0_mu_H4.push_back(g3x_nrCl0);
        	g3x_y1_mu_H4.push_back(g3x_nrCl1);
        	g3x_y2_mu_H4.push_back(g3x_nrCl2);
        	g3x_y3_mu_H4.push_back(g3x_nrCl3);
        	g3x_y4_mu_H4.push_back(g3x_nrCl4);
        	g3x_y5_mu_H4.push_back(g3x_nrCl5);

        	//================read data from hg1y======================
			double g1y_nrCl0 = hg1y->GetBinContent(1);
			double g1y_nrCl1 = hg1y->GetBinContent(2);
			double g1y_nrCl2 = hg1y->GetBinContent(3);
			double g1y_nrCl3 = hg1y->GetBinContent(4);
			double g1y_nrCl4 = hg1y->GetBinContent(5);
			double g1y_nrCl5 = hg1y->GetBinContent(6);

			if (verbose) cout << files << ": " << g1y_nrCl0 << ", " << g1y_nrCl1 << ", " << g1y_nrCl2 << ", " << g1y_nrCl3 << ", " << g1y_nrCl4 << ", " << g1y_nrCl5 << endl;
        	
        	g1y_y0_mu_H4.push_back(g1y_nrCl0);
        	g1y_y1_mu_H4.push_back(g1y_nrCl1);
        	g1y_y2_mu_H4.push_back(g1y_nrCl2);
        	g1y_y3_mu_H4.push_back(g1y_nrCl3);
        	g1y_y4_mu_H4.push_back(g1y_nrCl4);
        	g1y_y5_mu_H4.push_back(g1y_nrCl5);

        	//================read data from hg2y======================
			double g2y_nrCl0 = hg2y->GetBinContent(1);
			double g2y_nrCl1 = hg2y->GetBinContent(2);
			double g2y_nrCl2 = hg2y->GetBinContent(3);
			double g2y_nrCl3 = hg2y->GetBinContent(4);
			double g2y_nrCl4 = hg2y->GetBinContent(5);
			double g2y_nrCl5 = hg2y->GetBinContent(6);

			if (verbose) cout << files << ": " << g2y_nrCl0 << ", " << g2y_nrCl1 << ", " << g2y_nrCl2 << ", " << g2y_nrCl3 << ", " << g2y_nrCl4 << ", " << g2y_nrCl5 << endl;
        	
        	g2y_y0_mu_H4.push_back(g2y_nrCl0);
        	g2y_y1_mu_H4.push_back(g2y_nrCl1);
        	g2y_y2_mu_H4.push_back(g2y_nrCl2);
        	g2y_y3_mu_H4.push_back(g2y_nrCl3);
        	g2y_y4_mu_H4.push_back(g2y_nrCl4);
        	g2y_y5_mu_H4.push_back(g2y_nrCl5);

        	//================read data from hg3y======================
			double g3y_nrCl0 = hg3y->GetBinContent(1);
			double g3y_nrCl1 = hg3y->GetBinContent(2);
			double g3y_nrCl2 = hg3y->GetBinContent(3);
			double g3y_nrCl3 = hg3y->GetBinContent(4);
			double g3y_nrCl4 = hg3y->GetBinContent(5);
			double g3y_nrCl5 = hg3y->GetBinContent(6);

			if (verbose) cout << files << ": " << g3y_nrCl0 << ", " << g3y_nrCl1 << ", " << g3y_nrCl2 << ", " << g3y_nrCl3 << ", " << g3y_nrCl4 << ", " << g3y_nrCl5 << endl;
        	
        	g3y_y0_mu_H4.push_back(g3y_nrCl0);
        	g3y_y1_mu_H4.push_back(g3y_nrCl1);
        	g3y_y2_mu_H4.push_back(g3y_nrCl2);
        	g3y_y3_mu_H4.push_back(g3y_nrCl3);
        	g3y_y4_mu_H4.push_back(g3y_nrCl4);
        	g3y_y5_mu_H4.push_back(g3y_nrCl5);


        	f->Close();
        	return 0;
}


int process_piH4 (string files)
{
	        string rootfile= "NumberOfClusters/";
        	rootfile = rootfile.append(files) ;
        	TFile* f = TFile::Open(rootfile.c_str(), "READ");
        	//f->ls();

        	TH1F * hg1x = (TH1F*)f->Get("Number of clusters on g1x;2");
			TH1F * hg1y = (TH1F*)f->Get("Number of clusters on g1y;2");
			TH1F * hg2x = (TH1F*)f->Get("Number of clusters on g2x;2");
			TH1F * hg2y = (TH1F*)f->Get("Number of clusters on g2y;2");
			TH1F * hg3x = (TH1F*)f->Get("Number of clusters on g3x;2");
			TH1F * hg3y = (TH1F*)f->Get("Number of clusters on g3y;2");

			//================read data from hg1x======================
			double g1x_nrCl0 = hg1x->GetBinContent(1);
			double g1x_nrCl1 = hg1x->GetBinContent(2);
			double g1x_nrCl2 = hg1x->GetBinContent(3);
			double g1x_nrCl3 = hg1x->GetBinContent(4);
			double g1x_nrCl4 = hg1x->GetBinContent(5);
			double g1x_nrCl5 = hg1x->GetBinContent(6);

			if (verbose) cout << files << ": " << g1x_nrCl0 << ", " << g1x_nrCl1 << ", " << g1x_nrCl2 << ", " << g1x_nrCl3 << ", " << g1x_nrCl4 << ", " << g1x_nrCl5 << endl;
        	
        	g1x_y0_pi_H4.push_back(g1x_nrCl0);
        	g1x_y1_pi_H4.push_back(g1x_nrCl1);
        	g1x_y2_pi_H4.push_back(g1x_nrCl2);
        	g1x_y3_pi_H4.push_back(g1x_nrCl3);
        	g1x_y4_pi_H4.push_back(g1x_nrCl4);
        	g1x_y5_pi_H4.push_back(g1x_nrCl5);

        	//================read data from hg2x======================
			double g2x_nrCl0 = hg2x->GetBinContent(1);
			double g2x_nrCl1 = hg2x->GetBinContent(2);
			double g2x_nrCl2 = hg2x->GetBinContent(3);
			double g2x_nrCl3 = hg2x->GetBinContent(4);
			double g2x_nrCl4 = hg2x->GetBinContent(5);
			double g2x_nrCl5 = hg2x->GetBinContent(6);

			if (verbose) cout << files << ": " << g2x_nrCl0 << ", " << g2x_nrCl1 << ", " << g2x_nrCl2 << ", " << g2x_nrCl3 << ", " << g2x_nrCl4 << ", " << g2x_nrCl5 << endl;
        	
        	g2x_y0_pi_H4.push_back(g2x_nrCl0);
        	g2x_y1_pi_H4.push_back(g2x_nrCl1);
        	g2x_y2_pi_H4.push_back(g2x_nrCl2);
        	g2x_y3_pi_H4.push_back(g2x_nrCl3);
        	g2x_y4_pi_H4.push_back(g2x_nrCl4);
        	g2x_y5_pi_H4.push_back(g2x_nrCl5);


        	//================read data from hg3x======================
			double g3x_nrCl0 = hg3x->GetBinContent(1);
			double g3x_nrCl1 = hg3x->GetBinContent(2);
			double g3x_nrCl2 = hg3x->GetBinContent(3);
			double g3x_nrCl3 = hg3x->GetBinContent(4);
			double g3x_nrCl4 = hg3x->GetBinContent(5);
			double g3x_nrCl5 = hg3x->GetBinContent(6);

			if (verbose) cout << files << ": " << g3x_nrCl0 << ", " << g3x_nrCl1 << ", " << g3x_nrCl2 << ", " << g3x_nrCl3 << ", " << g3x_nrCl4 << ", " << g3x_nrCl5 << endl;
        	
        	g3x_y0_pi_H4.push_back(g3x_nrCl0);
        	g3x_y1_pi_H4.push_back(g3x_nrCl1);
        	g3x_y2_pi_H4.push_back(g3x_nrCl2);
        	g3x_y3_pi_H4.push_back(g3x_nrCl3);
        	g3x_y4_pi_H4.push_back(g3x_nrCl4);
        	g3x_y5_pi_H4.push_back(g3x_nrCl5);

        	//================read data from hg1y======================
			double g1y_nrCl0 = hg1y->GetBinContent(1);
			double g1y_nrCl1 = hg1y->GetBinContent(2);
			double g1y_nrCl2 = hg1y->GetBinContent(3);
			double g1y_nrCl3 = hg1y->GetBinContent(4);
			double g1y_nrCl4 = hg1y->GetBinContent(5);
			double g1y_nrCl5 = hg1y->GetBinContent(6);

			if (verbose) cout << files << ": " << g1y_nrCl0 << ", " << g1y_nrCl1 << ", " << g1y_nrCl2 << ", " << g1y_nrCl3 << ", " << g1y_nrCl4 << ", " << g1y_nrCl5 << endl;
        	
        	g1y_y0_pi_H4.push_back(g1y_nrCl0);
        	g1y_y1_pi_H4.push_back(g1y_nrCl1);
        	g1y_y2_pi_H4.push_back(g1y_nrCl2);
        	g1y_y3_pi_H4.push_back(g1y_nrCl3);
        	g1y_y4_pi_H4.push_back(g1y_nrCl4);
        	g1y_y5_pi_H4.push_back(g1y_nrCl5);

        	//================read data from hg2y======================
			double g2y_nrCl0 = hg2y->GetBinContent(1);
			double g2y_nrCl1 = hg2y->GetBinContent(2);
			double g2y_nrCl2 = hg2y->GetBinContent(3);
			double g2y_nrCl3 = hg2y->GetBinContent(4);
			double g2y_nrCl4 = hg2y->GetBinContent(5);
			double g2y_nrCl5 = hg2y->GetBinContent(6);

			if (verbose) cout << files << ": " << g2y_nrCl0 << ", " << g2y_nrCl1 << ", " << g2y_nrCl2 << ", " << g2y_nrCl3 << ", " << g2y_nrCl4 << ", " << g2y_nrCl5 << endl;
        	
        	g2y_y0_pi_H4.push_back(g2y_nrCl0);
        	g2y_y1_pi_H4.push_back(g2y_nrCl1);
        	g2y_y2_pi_H4.push_back(g2y_nrCl2);
        	g2y_y3_pi_H4.push_back(g2y_nrCl3);
        	g2y_y4_pi_H4.push_back(g2y_nrCl4);
        	g2y_y5_pi_H4.push_back(g2y_nrCl5);

        	//================read data from hg3y======================
			double g3y_nrCl0 = hg3y->GetBinContent(1);
			double g3y_nrCl1 = hg3y->GetBinContent(2);
			double g3y_nrCl2 = hg3y->GetBinContent(3);
			double g3y_nrCl3 = hg3y->GetBinContent(4);
			double g3y_nrCl4 = hg3y->GetBinContent(5);
			double g3y_nrCl5 = hg3y->GetBinContent(6);

			if (verbose) cout << files << ": " << g3y_nrCl0 << ", " << g3y_nrCl1 << ", " << g3y_nrCl2 << ", " << g3y_nrCl3 << ", " << g3y_nrCl4 << ", " << g3y_nrCl5 << endl;
        	
        	g3y_y0_pi_H4.push_back(g3y_nrCl0);
        	g3y_y1_pi_H4.push_back(g3y_nrCl1);
        	g3y_y2_pi_H4.push_back(g3y_nrCl2);
        	g3y_y3_pi_H4.push_back(g3y_nrCl3);
        	g3y_y4_pi_H4.push_back(g3y_nrCl4);
        	g3y_y5_pi_H4.push_back(g3y_nrCl5);


        	f->Close();
        	return 0;
}


//**************************************************************MAIN function**************************************************************************************************

int main()
{
	cout << "Choose VFAT scheme to be used for H4 (options: from 1 to 5):" << endl;
	int VFATscheme;
	cin >> VFATscheme;
	TString scheme=Form("%i", VFATscheme);

	//get directory content
    string dir = string("NumberOfClusters");
    vector<string> files = vector<string>();
    getdir(dir,files);

    TCanvas *canv1 = new TCanvas("canv1","H2 - muons",2000,1000); //for H2, muons
    TString H2mutitle = "Muon runs - H2 TB";
	TPad *c = new TPad("c","pad with graphs",0,0,1,0.93);
	c->Draw();
	c->cd();
    c->Divide(3,2); 

    TCanvas *canv2 = new TCanvas("canv2","H2 - pions",2000,1000); //for H2, pions
    TString H2pititle = "Pion runs - H2 TB";
	TPad *c2 = new TPad("c2","pad with graphs",0,0,1,0.93);
	c2->Draw();
	c2->cd();
    c2->Divide(3,2);

    TCanvas *canv3 = new TCanvas("canv3","H4 - muons",2000,1000); //for H4, muons
    TString H4mutitle = "Muon runs - H4 TB - VFAT scheme "+scheme;
	TPad *c3 = new TPad("c3","pad with graphs",0,0,1,0.93);
	c3->Draw();
	c3->cd();
    c3->Divide(3,2);

    TCanvas *canv4 = new TCanvas("c4","H4 - pions",2000,1000); //for H4, pions
    TString H4pititle = "Pion runs - H4 TB - VFAT scheme "+scheme;
	TPad *c4 = new TPad("c4","pad with graphs",0,0,1,0.93);
	c4->Draw();
	c4->cd();
    c4->Divide(3,2);


    for (unsigned int i = 0;i < files.size();i++)
    	{//start: process files in the folder
        if (verbose) cout << files[i] << endl;

        //==========================================start:H2 muon runs======================================================
        if ( files[i] == "NumberOfClusters_R60_R64.root" )
        	{
        	double hv=3928;
        	double curr=1436;
        	x_mu_H2.push_back(hv);
        	curr_mu_H2.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH2(files[i]);
        	}
        if ( files[i] == "NumberOfClusters_R65_R71.root")
        	{
        	double hv=3904;
        	double curr=1426;
        	x_mu_H2.push_back(hv);
        	curr_mu_H2.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH2(files[i]);
        	}
        if ( files[i] == "NumberOfClusters_R72_R77.root" )
        	{
        	double hv=3882;
        	double curr=1419;
        	x_mu_H2.push_back(hv);
        	curr_mu_H2.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH2(files[i]);
        	}
        if ( files[i] == "NumberOfClusters_R78_R82.root" )
        	{
        	double hv=3857;
        	double curr=1409;
        	x_mu_H2.push_back(hv);
        	curr_mu_H2.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH2(files[i]);
        	}
        if ( files[i] == "NumberOfClusters_R83_R88.root" )
        	{
        	double hv=3820;
        	double curr=1400;
        	x_mu_H2.push_back(hv);
        	curr_mu_H2.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH2(files[i]);
        	}
        if ( files[i] == "NumberOfClusters_R89_RR94.root" )
        	{
        	double hv=3805;
        	double curr=1390;
        	x_mu_H2.push_back(hv);
        	curr_mu_H2.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH2(files[i]);
        	}
        if ( files[i] == "NumberOfClusters_R95_R100.root" )
        	{
        	double hv=3780.60;
        	double curr=1381.60;
        	x_mu_H2.push_back(hv);
        	curr_mu_H2.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH2(files[i]);
        	}
        if ( files[i] == "NumberOfClusters_R101_R106.root" )
        	{
        	double hv=3756;
        	double curr=1373;
        	x_mu_H2.push_back(hv);
        	curr_mu_H2.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH2(files[i]);
        	}
        if ( files[i] == "NumberOfClusters_R108_R113.root" )
        	{
        	double hv=3928;
        	double curr=1436;
        	x_mu_H2.push_back(hv);
        	curr_mu_H2.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH2(files[i]);
        	}
        if ( files[i] == "NumberOfClusters_R114_R118.root" )
        	{
        	double hv=3904;
        	double curr=1426;
        	x_mu_H2.push_back(hv);
        	curr_mu_H2.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH2(files[i]);
        	}
        if ( files[i] == "NumberOfClusters_R119_R123.root" )
        	{
        	double hv=3882;
        	double curr=1418.75;
        	x_mu_H2.push_back(hv);
        	curr_mu_H2.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH2(files[i]);
        	}
        //==========================================end:H2 muon runs======================================================

        //==========================================start:H2 pion runs======================================================
        if ( files[i] == "NumberOfClusters_R2_R9.root" )
        	{
        	double hv=3928;
        	double curr=1435.50;
        	x_pi_H2.push_back(hv);
        	curr_pi_H2.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_piH2(files[i]);
        	}
        if ( files[i] == "NumberOfClusters_R10_R16.root" )
        	{
        	double hv=3904;
        	double curr=1427;
        	x_pi_H2.push_back(hv);
        	curr_pi_H2.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_piH2(files[i]);
        	}
        if ( files[i] == "NumberOfClusters_R17_R23.root" )
        	{
        	double hv=3882;
        	double curr=1418;
        	x_pi_H2.push_back(hv);
        	curr_pi_H2.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_piH2(files[i]);
        	}
        if ( files[i] == "NumberOfClusters_R24_R28.root" )
        	{
        	double hv=3877;
        	double curr=1409;
        	x_pi_H2.push_back(hv);
        	curr_pi_H2.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_piH2(files[i]);
        	}
        if ( files[i] == "NumberOfClusters_R29_R35.root" )
        	{
        	double hv=3830;
        	double curr=1400;
        	x_pi_H2.push_back(hv);
        	curr_pi_H2.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_piH2(files[i]);
        	}
        if ( files[i] == "NumberOfClusters_R36_R41.root" )
        	{
        	double hv=3805;
        	double curr=1389.95;
        	x_pi_H2.push_back(hv);
        	curr_pi_H2.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_piH2(files[i]);
        	}
        if ( files[i] == "NumberOfClusters_R42_R49.root" )
        	{
        	double hv=3780.60;
        	double curr=1381.60;
        	x_pi_H2.push_back(hv);
        	curr_pi_H2.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_piH2(files[i]);
        	}
        if ( files[i] == "NumberOfClusters_R50_R54.root" )
        	{
        	double hv=3756;
        	double curr=1373;
        	x_pi_H2.push_back(hv);
        	curr_pi_H2.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_piH2(files[i]);
        	}
        if ( files[i] == "NumberOfClusters_R55_R59.root" )
        	{
        	double hv=3928;
        	double curr=1436;
        	x_pi_H2.push_back(hv);
        	curr_pi_H2.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_piH2(files[i]);
        	}
        //==========================================end:H2 pion runs======================================================

        //==========================================start:H4 muon runs======================================================
		if ( files[i] == "NumberOfClusters_R124_R129.root" && VFATscheme == 1 )
			{
        	double hv=4370;
        	double curr=1597;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R130_R134.root" && VFATscheme == 1 )
			{
        	double hv=4335;
        	double curr=1564;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R135_R140.root" && VFATscheme == 1 )
			{
        	double hv=4300;
        	double curr=1572;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R141_R145.root" && VFATscheme == 1 )
			{
        	double hv=4275;
        	double curr=1562;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R146_R150.root" && VFATscheme == 1 )
			{
        	double hv=4250;
        	double curr=1553;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R151_R155.root" && VFATscheme == 1 )
			{
        	double hv=4225;
        	double curr=1544;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R156_R160.root" && VFATscheme == 1 )
			{
        	double hv=4200;
        	double curr=1535;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R161_R165.root" && VFATscheme == 1 )
			{
        	double hv=4175;
        	double curr=1526;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R166_R171.root" && VFATscheme == 1 )
			{
        	double hv=4150;
        	double curr=1517;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R172_R176.root" && VFATscheme == 1 )
			{
        	double hv=4125;
        	double curr=1507;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R177_R181.root" && VFATscheme == 1 )
			{
        	double hv=4100;
        	double curr=1498;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R182_R186.root" && VFATscheme == 1 )
			{
        	double hv=4370;
        	double curr=1597;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}

		if ( files[i] == "NumberOfClusters_R187_R192.root" && VFATscheme == 2 )
			{
        	double hv=4350;
        	double curr=1590;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R193_R197.root" && VFATscheme == 2 )
			{
        	double hv=4335;
        	double curr=1584;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R198_R203.root" && VFATscheme == 2 )
			{
        	double hv=4320;
        	double curr=1579;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R204_R210.root" && VFATscheme == 2 )
			{
        	double hv=4300;
        	double curr=1571;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R211_R218.root" && VFATscheme == 2 )
			{
        	double hv=4275;
        	double curr=1562;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R219_R225.root" && VFATscheme == 2 )
			{
        	double hv=4250;
        	double curr=1553;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R226_R231.root" && VFATscheme == 2 )
			{
        	double hv=4225;
        	double curr=1544;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R232_R238.root" && VFATscheme == 2 )
			{
        	double hv=4200;
        	double curr=1434;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}

		if ( files[i] == "NumberOfClusters_R239_R244.root" && VFATscheme == 3 )
			{
        	double hv=4370;
        	double curr=1597;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R245_R251.root" && VFATscheme == 3 )
			{
        	double hv=4350;
        	double curr=1589;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R252_R260.root" && VFATscheme == 3 )
			{
        	double hv=4330;
        	double curr=1582;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R261_R269.root" && VFATscheme == 3 )
			{
        	double hv=4320;
        	double curr=1579;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R270_R275.root" && VFATscheme == 3 )
			{
        	double hv=4320;
        	double curr=1579;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R276_R281.root" && VFATscheme == 3 )
			{
        	double hv=4300;
        	double curr=1572;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R282_R287.root" && VFATscheme == 3 )
			{
        	double hv=4275;
        	double curr=1562;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R288_R292.root" && VFATscheme == 3 )
			{
        	double hv=4250;
        	double curr=1553;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}

		if ( files[i] == "NumberOfClusters_R293_R296.root" && VFATscheme == 4 )
			{
        	double hv=4350;
        	double curr=1589;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R297_R301.root" && VFATscheme == 4 )
			{
        	double hv=4335;
        	double curr=1584;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R302_R306.root" && VFATscheme == 4 )
			{
        	double hv=4320;
        	double curr=1579;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R307_R311.root" && VFATscheme == 4 )
			{
        	double hv=4300;
        	double curr=1571;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R312_R316.root" && VFATscheme == 4 )
			{
        	double hv=4275;
        	double curr=1562;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R317_R322.root" && VFATscheme == 4 )
			{
        	double hv=4250;
        	double curr=1553;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R323_R327.root" && VFATscheme == 4 )
			{
        	double hv=4225;
        	double curr=1544;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R328_R332.root" && VFATscheme == 4 )
			{
        	double hv=4200;
        	double curr=1535;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}

		if ( files[i] == "NumberOfClusters_R375_R378.root" && VFATscheme == 5 )
			{
        	double hv=4370;
        	double curr=1596;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R379_R382.root" && VFATscheme == 5 )
			{
        	double hv=4350;
        	double curr=1590;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R383_R386.root" && VFATscheme == 5 )
			{
        	double hv=4335;
        	double curr=1584;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R387_R390.root" && VFATscheme == 5 )
			{
        	double hv=4320;
        	double curr=1578;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R391_R394.root" && VFATscheme == 5 )
			{
        	double hv=4300;
        	double curr=1571;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R395_R398.root" && VFATscheme == 5 )
			{
        	double hv=4275;
        	double curr=1562;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R399_R402.root" && VFATscheme == 5 )
			{
        	double hv=4250;
        	double curr=1552;
        	x_mu_H4.push_back(hv);
        	curr_mu_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_muH4(files[i]);
        	}
        //==========================================end:H4 muon runs======================================================


        //==========================================start:H4 pion runs======================================================
		if ( files[i] == "NumberOfClusters_R333_R337.root" && VFATscheme == 4 )
			{
        	double hv=4370;
        	double curr=1597;
        	x_pi_H4.push_back(hv);
        	curr_pi_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_piH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R338_R343.root" && VFATscheme == 4 )
			{
        	double hv=4350;
        	double curr=1590;
        	x_pi_H4.push_back(hv);
        	curr_pi_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_piH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R344_R348.root" && VFATscheme == 4 )
			{
        	double hv=4335;
        	double curr=1584;
        	x_pi_H4.push_back(hv);
        	curr_pi_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_piH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R349_R353.root" && VFATscheme == 4 )
			{
        	double hv=4320;
        	double curr=1578;
        	x_pi_H4.push_back(hv);
        	curr_pi_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_piH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R354_R357.root" && VFATscheme == 4 )
			{
        	double hv=4300;
        	double curr=1571;
        	x_pi_H4.push_back(hv);
        	curr_pi_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_piH4(files[i]);
        	}

		if ( files[i] == "NumberOfClusters_R359_R362.root" && VFATscheme == 5 )
			{
        	double hv=4275;
        	double curr=1562;
        	x_pi_H4.push_back(hv);
        	curr_pi_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_piH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R363_R366.root" && VFATscheme == 5 )
			{
        	double hv=4250;
        	double curr=1553;
        	x_pi_H4.push_back(hv);
        	curr_pi_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_piH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R367_R370.root" && VFATscheme == 5 )
			{
        	double hv=4225;
        	double curr=1543;
        	x_pi_H4.push_back(hv);
        	curr_pi_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_piH4(files[i]);
        	}
		if ( files[i] == "NumberOfClusters_R371_R374.root" && VFATscheme == 5 )
			{
        	double hv=4200;
        	double curr=1534;
        	x_pi_H4.push_back(hv);
        	curr_pi_H4.push_back(curr);
        	if (verbose) cout << "\nLast entries: " << hv << "	" << curr << "\n" << endl;
        	process_piH4(files[i]);
        	}
        //==========================================end:H4 pion runs======================================================

    	}//end: process files in the folder


//===========================================START: draw canvas for MUON runs at H2======================================================================================
    //==========================TGraphs for g1x at H2==================================================================================
    c->cd(1);

	c->cd(1)->SetGridy(10);

    TGraph *g0_g1x_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g1x_y0_mu_H2[0]) );
    g0_g1x_muH2->SetMarkerColor(kBlack);
    g0_g1x_muH2->SetTitle("g1x");
    g0_g1x_muH2->SetMarkerStyle(21);
    g0_g1x_muH2->SetMarkerSize(0.8);
    g0_g1x_muH2->GetXaxis()->SetTitleSize(0.05);
	g0_g1x_muH2->GetYaxis()->SetTitleSize(0.05);
	g0_g1x_muH2->GetXaxis()->SetLabelSize(0.05);
	g0_g1x_muH2->GetYaxis()->SetLabelSize(0.05);
    g0_g1x_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g0_g1x_muH2->GetYaxis()->SetTitle("Entries [%]");
    g0_g1x_muH2->GetXaxis()->SetLimits(3750,3950);
    g0_g1x_muH2->GetXaxis()->SetNdivisions(506);
    g0_g1x_muH2->GetYaxis()->SetRangeUser(0,100);
    g0_g1x_muH2->Draw("AP");

    c->cd(1);
    TGraph *g1_g1x_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g1x_y1_mu_H2[0]) );
    g1_g1x_muH2->SetMarkerColor(kRed);
    g1_g1x_muH2->SetTitle("g1x");
    g1_g1x_muH2->SetMarkerStyle(21);
    g1_g1x_muH2->SetMarkerSize(0.8);
    g1_g1x_muH2->GetXaxis()->SetTitleSize(0.05);
	g1_g1x_muH2->GetYaxis()->SetTitleSize(0.05);
	g1_g1x_muH2->GetXaxis()->SetLabelSize(0.05);
	g1_g1x_muH2->GetYaxis()->SetLabelSize(0.05);
    g1_g1x_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g1_g1x_muH2->GetYaxis()->SetTitle("Entries [%]");
    g1_g1x_muH2->Draw("SAMEP");

	c->cd(1);
    TGraph *g2_g1x_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g1x_y2_mu_H2[0]) );
    g2_g1x_muH2->SetMarkerColor(kGreen);
    g2_g1x_muH2->SetTitle("g1x");
    g2_g1x_muH2->SetMarkerStyle(21);
    g2_g1x_muH2->SetMarkerSize(0.8);
    g2_g1x_muH2->GetXaxis()->SetTitleSize(0.05);
	g2_g1x_muH2->GetYaxis()->SetTitleSize(0.05);
	g2_g1x_muH2->GetXaxis()->SetLabelSize(0.05);
	g2_g1x_muH2->GetYaxis()->SetLabelSize(0.05);
    g2_g1x_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g2_g1x_muH2->GetYaxis()->SetTitle("Entries [%]");
    g2_g1x_muH2->Draw("SAMEP");

    c->cd(1);
    TGraph *g3_g1x_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g1x_y3_mu_H2[0]) );
    g3_g1x_muH2->SetMarkerColor(kBlue);
    g3_g1x_muH2->SetTitle("g1x");
    g3_g1x_muH2->SetMarkerStyle(21);
    g3_g1x_muH2->SetMarkerSize(0.8);
    g3_g1x_muH2->GetXaxis()->SetTitleSize(0.05);
	g3_g1x_muH2->GetYaxis()->SetTitleSize(0.05);
	g3_g1x_muH2->GetXaxis()->SetLabelSize(0.05);
	g3_g1x_muH2->GetYaxis()->SetLabelSize(0.05);
    g3_g1x_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g3_g1x_muH2->GetYaxis()->SetTitle("Entries [%]");
    g3_g1x_muH2->Draw("SAMEP");

    c->cd(1);
    TGraph *g4_g1x_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g1x_y4_mu_H2[0]) );
    g4_g1x_muH2->SetMarkerColor(kMagenta);
    g4_g1x_muH2->SetTitle("g1x");
    g4_g1x_muH2->SetMarkerStyle(21);
    g4_g1x_muH2->SetMarkerSize(0.8);
    g4_g1x_muH2->GetXaxis()->SetTitleSize(0.05);
	g4_g1x_muH2->GetYaxis()->SetTitleSize(0.05);
	g4_g1x_muH2->GetXaxis()->SetLabelSize(0.05);
	g4_g1x_muH2->GetYaxis()->SetLabelSize(0.05);
    g4_g1x_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g4_g1x_muH2->GetYaxis()->SetTitle("Entries [%]");
    g4_g1x_muH2->Draw("SAMEP");

    c->cd(1);
    TGraph *g5_g1x_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g1x_y5_mu_H2[0]) );
    g5_g1x_muH2->SetMarkerColor(kCyan);
    g5_g1x_muH2->SetTitle("g1x");
    g5_g1x_muH2->SetMarkerStyle(21);
    g5_g1x_muH2->SetMarkerSize(0.8);
    g5_g1x_muH2->GetXaxis()->SetTitleSize(0.05);
	g5_g1x_muH2->GetYaxis()->SetTitleSize(0.05);
	g5_g1x_muH2->GetXaxis()->SetLabelSize(0.05);
	g5_g1x_muH2->GetYaxis()->SetLabelSize(0.05);
    g5_g1x_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g5_g1x_muH2->GetYaxis()->SetTitle("Entries [%]");
    g5_g1x_muH2->Draw("SAMEP");    
    //==========================end: TGraphs for g1x at H2=============================================================================


    //==========================TGraphs for g1y at H2==================================================================================
    c->cd(2);

	c->cd(2)->SetGridy(10);

    TGraph *g0_g1y_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g1y_y0_mu_H2[0]) );
    g0_g1y_muH2->SetMarkerColor(kBlack);
    g0_g1y_muH2->SetTitle("g1y");
    g0_g1y_muH2->SetMarkerStyle(21);
    g0_g1y_muH2->SetMarkerSize(0.8);
    g0_g1y_muH2->GetXaxis()->SetTitleSize(0.05);
	g0_g1y_muH2->GetYaxis()->SetTitleSize(0.05);
	g0_g1y_muH2->GetXaxis()->SetLabelSize(0.05);
	g0_g1y_muH2->GetYaxis()->SetLabelSize(0.05);
    g0_g1y_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g0_g1y_muH2->GetYaxis()->SetTitle("Entries [%]");
    g0_g1y_muH2->GetXaxis()->SetLimits(3750,3950);
    g0_g1y_muH2->GetXaxis()->SetNdivisions(506);
    g0_g1y_muH2->GetYaxis()->SetRangeUser(0,100);
    g0_g1y_muH2->Draw("AP");

    c->cd(2);
    TGraph *g1_g1y_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g1y_y1_mu_H2[0]) );
    g1_g1y_muH2->SetMarkerColor(kRed);
    g1_g1y_muH2->SetTitle("g1y");
    g1_g1y_muH2->SetMarkerStyle(21);
    g1_g1y_muH2->SetMarkerSize(0.8);
    g1_g1y_muH2->GetXaxis()->SetTitleSize(0.05);
	g1_g1y_muH2->GetYaxis()->SetTitleSize(0.05);
	g1_g1y_muH2->GetXaxis()->SetLabelSize(0.05);
	g1_g1y_muH2->GetYaxis()->SetLabelSize(0.05);
    g1_g1y_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g1_g1y_muH2->GetYaxis()->SetTitle("Entries [%]");
    g1_g1y_muH2->Draw("SAMEP");

	c->cd(2);
    TGraph *g2_g1y_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g1y_y2_mu_H2[0]) );
    g2_g1y_muH2->SetMarkerColor(kGreen);
    g2_g1y_muH2->SetTitle("g1y");
    g2_g1y_muH2->SetMarkerStyle(21);
    g2_g1y_muH2->SetMarkerSize(0.8);
    g2_g1y_muH2->GetXaxis()->SetTitleSize(0.05);
	g2_g1y_muH2->GetYaxis()->SetTitleSize(0.05);
	g2_g1y_muH2->GetXaxis()->SetLabelSize(0.05);
	g2_g1y_muH2->GetYaxis()->SetLabelSize(0.05);
    g2_g1y_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g2_g1y_muH2->GetYaxis()->SetTitle("Entries [%]");
    g2_g1y_muH2->Draw("SAMEP");

    c->cd(2);
    TGraph *g3_g1y_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g1y_y3_mu_H2[0]) );
    g3_g1y_muH2->SetMarkerColor(kBlue);
    g3_g1y_muH2->SetTitle("g1y");
    g3_g1y_muH2->SetMarkerStyle(21);
    g3_g1y_muH2->SetMarkerSize(0.8);
    g3_g1y_muH2->GetXaxis()->SetTitleSize(0.05);
	g3_g1y_muH2->GetYaxis()->SetTitleSize(0.05);
	g3_g1y_muH2->GetXaxis()->SetLabelSize(0.05);
	g3_g1y_muH2->GetYaxis()->SetLabelSize(0.05);
    g3_g1y_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g3_g1y_muH2->GetYaxis()->SetTitle("Entries [%]");
    g3_g1y_muH2->Draw("SAMEP");

    c->cd(2);
    TGraph *g4_g1y_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g1y_y4_mu_H2[0]) );
    g4_g1y_muH2->SetMarkerColor(kMagenta);
    g4_g1y_muH2->SetTitle("g1y");
    g4_g1y_muH2->SetMarkerStyle(21);
    g4_g1y_muH2->SetMarkerSize(0.8);
    g4_g1y_muH2->GetXaxis()->SetTitleSize(0.05);
	g4_g1y_muH2->GetYaxis()->SetTitleSize(0.05);
	g4_g1y_muH2->GetXaxis()->SetLabelSize(0.05);
	g4_g1y_muH2->GetYaxis()->SetLabelSize(0.05);
    g4_g1y_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g4_g1y_muH2->GetYaxis()->SetTitle("Entries [%]");
    g4_g1y_muH2->Draw("SAMEP");

    c->cd(2);
    TGraph *g5_g1y_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g1y_y5_mu_H2[0]) );
    g5_g1y_muH2->SetMarkerColor(kCyan);
    g5_g1y_muH2->SetTitle("g1y");
    g5_g1y_muH2->SetMarkerStyle(21);
    g5_g1y_muH2->SetMarkerSize(0.8);
    g5_g1y_muH2->GetXaxis()->SetTitleSize(0.05);
	g5_g1y_muH2->GetYaxis()->SetTitleSize(0.05);
	g5_g1y_muH2->GetXaxis()->SetLabelSize(0.05);
	g5_g1y_muH2->GetYaxis()->SetLabelSize(0.05);
    g5_g1y_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g5_g1y_muH2->GetYaxis()->SetTitle("Entries [%]");
    g5_g1y_muH2->Draw("SAMEP");    
    //==========================end: TGraphs for g1y at H2=============================================================================


    //==========================TGraphs for g2x at H2==================================================================================
    c->cd(3);

	c->cd(3)->SetGridy(10);

    TGraph *g0_g2x_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g2x_y0_mu_H2[0]) );
    g0_g2x_muH2->SetMarkerColor(kBlack);
    g0_g2x_muH2->SetTitle("g2x");
    g0_g2x_muH2->SetMarkerStyle(21);
    g0_g2x_muH2->SetMarkerSize(0.8);
    g0_g2x_muH2->GetXaxis()->SetTitleSize(0.05);
	g0_g2x_muH2->GetYaxis()->SetTitleSize(0.05);
	g0_g2x_muH2->GetXaxis()->SetLabelSize(0.05);
	g0_g2x_muH2->GetYaxis()->SetLabelSize(0.05);
    g0_g2x_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g0_g2x_muH2->GetYaxis()->SetTitle("Entries [%]");
    g0_g2x_muH2->GetXaxis()->SetLimits(3750,3950);
    g0_g2x_muH2->GetXaxis()->SetNdivisions(506);
    g0_g2x_muH2->GetYaxis()->SetRangeUser(0,100);
    g0_g2x_muH2->Draw("AP");

    c->cd(3);
    TGraph *g1_g2x_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g2x_y1_mu_H2[0]) );
    g1_g2x_muH2->SetMarkerColor(kRed);
    g1_g2x_muH2->SetTitle("g2x");
    g1_g2x_muH2->SetMarkerStyle(21);
    g1_g2x_muH2->SetMarkerSize(0.8);
    g1_g2x_muH2->GetXaxis()->SetTitleSize(0.05);
	g1_g2x_muH2->GetYaxis()->SetTitleSize(0.05);
	g1_g2x_muH2->GetXaxis()->SetLabelSize(0.05);
	g1_g2x_muH2->GetYaxis()->SetLabelSize(0.05);
    g1_g2x_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g1_g2x_muH2->GetYaxis()->SetTitle("Entries [%]");
    g1_g2x_muH2->Draw("SAMEP");

	c->cd(3);
    TGraph *g2_g2x_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g2x_y2_mu_H2[0]) );
    g2_g2x_muH2->SetMarkerColor(kGreen);
    g2_g2x_muH2->SetTitle("g2x");
    g2_g2x_muH2->SetMarkerStyle(21);
    g2_g2x_muH2->SetMarkerSize(0.8);
    g2_g2x_muH2->GetXaxis()->SetTitleSize(0.05);
	g2_g2x_muH2->GetYaxis()->SetTitleSize(0.05);
	g2_g2x_muH2->GetXaxis()->SetLabelSize(0.05);
	g2_g2x_muH2->GetYaxis()->SetLabelSize(0.05);
    g2_g2x_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g2_g2x_muH2->GetYaxis()->SetTitle("Entries [%]");
    g2_g2x_muH2->Draw("SAMEP");

    c->cd(3);
    TGraph *g3_g2x_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g2x_y3_mu_H2[0]) );
    g3_g2x_muH2->SetMarkerColor(kBlue);
    g3_g2x_muH2->SetTitle("g2x");
    g3_g2x_muH2->SetMarkerStyle(21);
    g3_g2x_muH2->SetMarkerSize(0.8);
    g3_g2x_muH2->GetXaxis()->SetTitleSize(0.05);
	g3_g2x_muH2->GetYaxis()->SetTitleSize(0.05);
	g3_g2x_muH2->GetXaxis()->SetLabelSize(0.05);
	g3_g2x_muH2->GetYaxis()->SetLabelSize(0.05);
    g3_g2x_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g3_g2x_muH2->GetYaxis()->SetTitle("Entries [%]");
    g3_g2x_muH2->Draw("SAMEP");

    c->cd(3);
    TGraph *g4_g2x_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g2x_y4_mu_H2[0]) );
    g4_g2x_muH2->SetMarkerColor(kMagenta);
    g4_g2x_muH2->SetTitle("g2x");
    g4_g2x_muH2->SetMarkerStyle(21);
    g4_g2x_muH2->SetMarkerSize(0.8);
    g4_g2x_muH2->GetXaxis()->SetTitleSize(0.05);
	g4_g2x_muH2->GetYaxis()->SetTitleSize(0.05);
	g4_g2x_muH2->GetXaxis()->SetLabelSize(0.05);
	g4_g2x_muH2->GetYaxis()->SetLabelSize(0.05);
    g4_g2x_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g4_g2x_muH2->GetYaxis()->SetTitle("Entries [%]");
    g4_g2x_muH2->Draw("SAMEP");

    c->cd(3);
    TGraph *g5_g2x_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g2x_y5_mu_H2[0]) );
    g5_g2x_muH2->SetMarkerColor(kCyan);
    g5_g2x_muH2->SetTitle("g2x");
    g5_g2x_muH2->SetMarkerStyle(21);
    g5_g2x_muH2->SetMarkerSize(0.8);
    g5_g2x_muH2->GetXaxis()->SetTitleSize(0.05);
	g5_g2x_muH2->GetYaxis()->SetTitleSize(0.05);
	g5_g2x_muH2->GetXaxis()->SetLabelSize(0.05);
	g5_g2x_muH2->GetYaxis()->SetLabelSize(0.05);
    g5_g2x_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g5_g2x_muH2->GetYaxis()->SetTitle("Entries [%]");
    g5_g2x_muH2->Draw("SAMEP");    
    //==========================end: TGraphs for g2x at H2=============================================================================

    //==========================TGraphs for g2y at H2==================================================================================
    c->cd(4);

	c->cd(4)->SetGridy(10);

    TGraph *g0_g2y_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g2y_y0_mu_H2[0]) );
    g0_g2y_muH2->SetMarkerColor(kBlack);
    g0_g2y_muH2->SetTitle("g2y");
    g0_g2y_muH2->SetMarkerStyle(21);
    g0_g2y_muH2->SetMarkerSize(0.8);
    g0_g2y_muH2->GetXaxis()->SetTitleSize(0.05);
	g0_g2y_muH2->GetYaxis()->SetTitleSize(0.05);
	g0_g2y_muH2->GetXaxis()->SetLabelSize(0.05);
	g0_g2y_muH2->GetYaxis()->SetLabelSize(0.05);
    g0_g2y_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g0_g2y_muH2->GetYaxis()->SetTitle("Entries [%]");
    g0_g2y_muH2->GetXaxis()->SetLimits(3750,3950);
    g0_g2y_muH2->GetXaxis()->SetNdivisions(506);
    g0_g2y_muH2->GetYaxis()->SetRangeUser(0,100);
    g0_g2y_muH2->Draw("AP");

    c->cd(4);
    TGraph *g1_g2y_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g2y_y1_mu_H2[0]) );
    g1_g2y_muH2->SetMarkerColor(kRed);
    g1_g2y_muH2->SetTitle("g2y");
    g1_g2y_muH2->SetMarkerStyle(21);
    g1_g2y_muH2->SetMarkerSize(0.8);
    g1_g2y_muH2->GetXaxis()->SetTitleSize(0.05);
	g1_g2y_muH2->GetYaxis()->SetTitleSize(0.05);
	g1_g2y_muH2->GetXaxis()->SetLabelSize(0.05);
	g1_g2y_muH2->GetYaxis()->SetLabelSize(0.05);
    g1_g2y_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g1_g2y_muH2->GetYaxis()->SetTitle("Entries [%]");
    g1_g2y_muH2->Draw("SAMEP");

	c->cd(4);
    TGraph *g2_g2y_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g2y_y2_mu_H2[0]) );
    g2_g2y_muH2->SetMarkerColor(kGreen);
    g2_g2y_muH2->SetTitle("g2y");
    g2_g2y_muH2->SetMarkerStyle(21);
    g2_g2y_muH2->SetMarkerSize(0.8);
    g2_g2y_muH2->GetXaxis()->SetTitleSize(0.05);
	g2_g2y_muH2->GetYaxis()->SetTitleSize(0.05);
	g2_g2y_muH2->GetXaxis()->SetLabelSize(0.05);
	g2_g2y_muH2->GetYaxis()->SetLabelSize(0.05);
    g2_g2y_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g2_g2y_muH2->GetYaxis()->SetTitle("Entries [%]");
    g2_g2y_muH2->Draw("SAMEP");

    c->cd(4);
    TGraph *g3_g2y_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g2y_y3_mu_H2[0]) );
    g3_g2y_muH2->SetMarkerColor(kBlue);
    g3_g2y_muH2->SetTitle("g2y");
    g3_g2y_muH2->SetMarkerStyle(21);
    g3_g2y_muH2->SetMarkerSize(0.8);
    g3_g2y_muH2->GetXaxis()->SetTitleSize(0.05);
	g3_g2y_muH2->GetYaxis()->SetTitleSize(0.05);
	g3_g2y_muH2->GetXaxis()->SetLabelSize(0.05);
	g3_g2y_muH2->GetYaxis()->SetLabelSize(0.05);
    g3_g2y_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g3_g2y_muH2->GetYaxis()->SetTitle("Entries [%]");
    g3_g2y_muH2->Draw("SAMEP");

    c->cd(4);
    TGraph *g4_g2y_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g2y_y4_mu_H2[0]) );
    g4_g2y_muH2->SetMarkerColor(kMagenta);
    g4_g2y_muH2->SetTitle("g2y");
    g4_g2y_muH2->SetMarkerStyle(21);
    g4_g2y_muH2->SetMarkerSize(0.8);
    g4_g2y_muH2->GetXaxis()->SetTitleSize(0.05);
	g4_g2y_muH2->GetYaxis()->SetTitleSize(0.05);
	g4_g2y_muH2->GetXaxis()->SetLabelSize(0.05);
	g4_g2y_muH2->GetYaxis()->SetLabelSize(0.05);
    g4_g2y_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g4_g2y_muH2->GetYaxis()->SetTitle("Entries [%]");
    g4_g2y_muH2->Draw("SAMEP");

    c->cd(4);
    TGraph *g5_g2y_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g2y_y5_mu_H2[0]) );
    g5_g2y_muH2->SetMarkerColor(kCyan);
    g5_g2y_muH2->SetTitle("g2y");
    g5_g2y_muH2->SetMarkerStyle(21);
    g5_g2y_muH2->SetMarkerSize(0.8);
    g5_g2y_muH2->GetXaxis()->SetTitleSize(0.05);
	g5_g2y_muH2->GetYaxis()->SetTitleSize(0.05);
	g5_g2y_muH2->GetXaxis()->SetLabelSize(0.05);
	g5_g2y_muH2->GetYaxis()->SetLabelSize(0.05);
    g5_g2y_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g5_g2y_muH2->GetYaxis()->SetTitle("Entries [%]");
    g5_g2y_muH2->Draw("SAMEP");    
    //==========================end: TGraphs for g2y at H2=============================================================================

    //==========================TGraphs for g3x at H2==================================================================================
    c->cd(5);

	c->cd(5)->SetGridy(10);

    TGraph *g0_g3x_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g3x_y0_mu_H2[0]) );
    g0_g3x_muH2->SetMarkerColor(kBlack);
    g0_g3x_muH2->SetTitle("g3x");
    g0_g3x_muH2->SetMarkerStyle(21);
    g0_g3x_muH2->SetMarkerSize(0.8);
    g0_g3x_muH2->GetXaxis()->SetTitleSize(0.05);
	g0_g3x_muH2->GetYaxis()->SetTitleSize(0.05);
	g0_g3x_muH2->GetXaxis()->SetLabelSize(0.05);
	g0_g3x_muH2->GetYaxis()->SetLabelSize(0.05);
    g0_g3x_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g0_g3x_muH2->GetYaxis()->SetTitle("Entries [%]");
    g0_g3x_muH2->GetXaxis()->SetLimits(3750,3950);
    g0_g3x_muH2->GetXaxis()->SetNdivisions(506);
    g0_g3x_muH2->GetYaxis()->SetRangeUser(0,100);
    g0_g3x_muH2->Draw("AP");

    c->cd(5);
    TGraph *g1_g3x_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g3x_y1_mu_H2[0]) );
    g1_g3x_muH2->SetMarkerColor(kRed);
    g1_g3x_muH2->SetTitle("g3x");
    g1_g3x_muH2->SetMarkerStyle(21);
    g1_g3x_muH2->SetMarkerSize(0.8);
    g1_g3x_muH2->GetXaxis()->SetTitleSize(0.05);
	g1_g3x_muH2->GetYaxis()->SetTitleSize(0.05);
	g1_g3x_muH2->GetXaxis()->SetLabelSize(0.05);
	g1_g3x_muH2->GetYaxis()->SetLabelSize(0.05);
    g1_g3x_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g1_g3x_muH2->GetYaxis()->SetTitle("Entries [%]");
    g1_g3x_muH2->Draw("SAMEP");

	c->cd(5);
    TGraph *g2_g3x_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g3x_y2_mu_H2[0]) );
    g2_g3x_muH2->SetMarkerColor(kGreen);
    g2_g3x_muH2->SetTitle("g3x");
    g2_g3x_muH2->SetMarkerStyle(21);
    g2_g3x_muH2->SetMarkerSize(0.8);
    g2_g3x_muH2->GetXaxis()->SetTitleSize(0.05);
	g2_g3x_muH2->GetYaxis()->SetTitleSize(0.05);
	g2_g3x_muH2->GetXaxis()->SetLabelSize(0.05);
	g2_g3x_muH2->GetYaxis()->SetLabelSize(0.05);
    g2_g3x_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g2_g3x_muH2->GetYaxis()->SetTitle("Entries [%]");
    g2_g3x_muH2->Draw("SAMEP");

    c->cd(5);
    TGraph *g3_g3x_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g3x_y3_mu_H2[0]) );
    g3_g3x_muH2->SetMarkerColor(kBlue);
    g3_g3x_muH2->SetTitle("g3x");
    g3_g3x_muH2->SetMarkerStyle(21);
    g3_g3x_muH2->SetMarkerSize(0.8);
    g3_g3x_muH2->GetXaxis()->SetTitleSize(0.05);
	g3_g3x_muH2->GetYaxis()->SetTitleSize(0.05);
	g3_g3x_muH2->GetXaxis()->SetLabelSize(0.05);
	g3_g3x_muH2->GetYaxis()->SetLabelSize(0.05);
    g3_g3x_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g3_g3x_muH2->GetYaxis()->SetTitle("Entries [%]");
    g3_g3x_muH2->Draw("SAMEP");

    c->cd(5);
    TGraph *g4_g3x_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g3x_y4_mu_H2[0]) );
    g4_g3x_muH2->SetMarkerColor(kMagenta);
    g4_g3x_muH2->SetTitle("g3x");
    g4_g3x_muH2->SetMarkerStyle(21);
    g4_g3x_muH2->SetMarkerSize(0.8);
    g4_g3x_muH2->GetXaxis()->SetTitleSize(0.05);
	g4_g3x_muH2->GetYaxis()->SetTitleSize(0.05);
	g4_g3x_muH2->GetXaxis()->SetLabelSize(0.05);
	g4_g3x_muH2->GetYaxis()->SetLabelSize(0.05);
    g4_g3x_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g4_g3x_muH2->GetYaxis()->SetTitle("Entries [%]");
    g4_g3x_muH2->Draw("SAMEP");

    c->cd(5);
    TGraph *g5_g3x_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g3x_y5_mu_H2[0]) );
    g5_g3x_muH2->SetMarkerColor(kCyan);
    g5_g3x_muH2->SetTitle("g3x");
    g5_g3x_muH2->SetMarkerStyle(21);
    g5_g3x_muH2->SetMarkerSize(0.8);
    g5_g3x_muH2->GetXaxis()->SetTitleSize(0.05);
	g5_g3x_muH2->GetYaxis()->SetTitleSize(0.05);
	g5_g3x_muH2->GetXaxis()->SetLabelSize(0.05);
	g5_g3x_muH2->GetYaxis()->SetLabelSize(0.05);
    g5_g3x_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g5_g3x_muH2->GetYaxis()->SetTitle("Entries [%]");
    g5_g3x_muH2->Draw("SAMEP");    
    //==========================end: TGraphs for g3x at H2=============================================================================


    //==========================TGraphs for g3y at H2==================================================================================
    c->cd(6);

	c->cd(6)->SetGridy(10);

    TGraph *g0_g3y_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g3y_y0_mu_H2[0]) );
    g0_g3y_muH2->SetMarkerColor(kBlack);
    g0_g3y_muH2->SetTitle("g3y");
    g0_g3y_muH2->SetMarkerStyle(21);
    g0_g3y_muH2->SetMarkerSize(0.8);
    g0_g3y_muH2->GetXaxis()->SetTitleSize(0.05);
	g0_g3y_muH2->GetYaxis()->SetTitleSize(0.05);
	g0_g3y_muH2->GetXaxis()->SetLabelSize(0.05);
	g0_g3y_muH2->GetYaxis()->SetLabelSize(0.05);
    g0_g3y_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g0_g3y_muH2->GetYaxis()->SetTitle("Entries [%]");
    g0_g3y_muH2->GetXaxis()->SetLimits(3750,3950);
    g0_g3y_muH2->GetXaxis()->SetNdivisions(506);
    g0_g3y_muH2->GetYaxis()->SetRangeUser(0,100);
    g0_g3y_muH2->Draw("AP");

    c->cd(6);
    TGraph *g1_g3y_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g3y_y1_mu_H2[0]) );
    g1_g3y_muH2->SetMarkerColor(kRed);
    g1_g3y_muH2->SetTitle("g3y");
    g1_g3y_muH2->SetMarkerStyle(21);
    g1_g3y_muH2->SetMarkerSize(0.8);
    g1_g3y_muH2->GetXaxis()->SetTitleSize(0.05);
	g1_g3y_muH2->GetYaxis()->SetTitleSize(0.05);
	g1_g3y_muH2->GetXaxis()->SetLabelSize(0.05);
	g1_g3y_muH2->GetYaxis()->SetLabelSize(0.05);
    g1_g3y_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g1_g3y_muH2->GetYaxis()->SetTitle("Entries [%]");
    g1_g3y_muH2->Draw("SAMEP");

	c->cd(6);
    TGraph *g2_g3y_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g3y_y2_mu_H2[0]) );
    g2_g3y_muH2->SetMarkerColor(kGreen);
    g2_g3y_muH2->SetTitle("g3y");
    g2_g3y_muH2->SetMarkerStyle(21);
    g2_g3y_muH2->SetMarkerSize(0.8);
    g2_g3y_muH2->GetXaxis()->SetTitleSize(0.05);
	g2_g3y_muH2->GetYaxis()->SetTitleSize(0.05);
	g2_g3y_muH2->GetXaxis()->SetLabelSize(0.05);
	g2_g3y_muH2->GetYaxis()->SetLabelSize(0.05);
    g2_g3y_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g2_g3y_muH2->GetYaxis()->SetTitle("Entries [%]");
    g2_g3y_muH2->Draw("SAMEP");

    c->cd(6);
    TGraph *g3_g3y_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g3y_y3_mu_H2[0]) );
    g3_g3y_muH2->SetMarkerColor(kBlue);
    g3_g3y_muH2->SetTitle("g3y");
    g3_g3y_muH2->SetMarkerStyle(21);
    g3_g3y_muH2->SetMarkerSize(0.8);
    g3_g3y_muH2->GetXaxis()->SetTitleSize(0.05);
	g3_g3y_muH2->GetYaxis()->SetTitleSize(0.05);
	g3_g3y_muH2->GetXaxis()->SetLabelSize(0.05);
	g3_g3y_muH2->GetYaxis()->SetLabelSize(0.05);
    g3_g3y_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g3_g3y_muH2->GetYaxis()->SetTitle("Entries [%]");
    g3_g3y_muH2->Draw("SAMEP");

    c->cd(6);
    TGraph *g4_g3y_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g3y_y4_mu_H2[0]) );
    g4_g3y_muH2->SetMarkerColor(kMagenta);
    g4_g3y_muH2->SetTitle("g3y");
    g4_g3y_muH2->SetMarkerStyle(21);
    g4_g3y_muH2->SetMarkerSize(0.8);
    g4_g3y_muH2->GetXaxis()->SetTitleSize(0.05);
	g4_g3y_muH2->GetYaxis()->SetTitleSize(0.05);
	g4_g3y_muH2->GetXaxis()->SetLabelSize(0.05);
	g4_g3y_muH2->GetYaxis()->SetLabelSize(0.05);
    g4_g3y_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g4_g3y_muH2->GetYaxis()->SetTitle("Entries [%]");
    g4_g3y_muH2->Draw("SAMEP");

    c->cd(6);
    TGraph *g5_g3y_muH2 = new TGraph ( x_mu_H2.size() , &(x_mu_H2[0]) , &(g3y_y5_mu_H2[0]) );
    g5_g3y_muH2->SetMarkerColor(kCyan);
    g5_g3y_muH2->SetTitle("g3y");
    g5_g3y_muH2->SetMarkerStyle(21);
    g5_g3y_muH2->SetMarkerSize(0.8);
    g5_g3y_muH2->GetXaxis()->SetTitleSize(0.05);
	g5_g3y_muH2->GetYaxis()->SetTitleSize(0.05);
	g5_g3y_muH2->GetXaxis()->SetLabelSize(0.05);
	g5_g3y_muH2->GetYaxis()->SetLabelSize(0.05);
    g5_g3y_muH2->GetXaxis()->SetTitle("Voltage [V]");
    g5_g3y_muH2->GetYaxis()->SetTitle("Entries [%]");
    g5_g3y_muH2->Draw("SAMEP");    
    //==========================end: TGraphs for g3y at H2=============================================================================

    canv1->cd();
    TPad *newpad = new TPad("newpad","a transparent pad",0,0,1,1);
	newpad->SetFillStyle(4000);
	newpad->Draw();
	newpad->cd();
	TPaveLabel *title = new TPaveLabel (0.01,0.94,0.3,0.98,H2mutitle);
	title->SetFillColor(kWhite);
	title->Draw();
    TLegend *leg = new TLegend(0.515, 0.92, 0.96, 0.995);
	leg->SetFillColor(0);
	leg-> SetNColumns(2);
	//leg->SetTextFont(62);
	leg->SetTextSize(0.02);
	//leg->SetHeader("");
	leg->AddEntry(g0_g1x_muH2, "Fraction of events with 0 Clusters", "p");
	leg->AddEntry(g1_g1x_muH2, "Fraction of events with 1 Clusters", "p");
	leg->AddEntry(g2_g1x_muH2, "Fraction of events with 2 Clusters", "p");
	leg->AddEntry(g3_g1x_muH2, "Fraction of events with 3 Clusters", "p");
	leg->AddEntry(g4_g1x_muH2, "Fraction of events with 4 Clusters", "p");
	leg->AddEntry(g5_g1x_muH2, "Fraction of events with 5 Clusters", "p");
	leg->Draw();
//===========================================END: draw canvas for MUON runs at H2======================================================================================







//===========================================START: draw canvas for PION runs at H2======================================================================================
    //==========================TGraphs for g1x at H2==================================================================================
    c2->cd(1);

	c2->cd(1)->SetGridy(10);

    TGraph *g0_g1x_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g1x_y0_pi_H2[0]) );
    g0_g1x_piH2->SetMarkerColor(kBlack);
    g0_g1x_piH2->SetTitle("g1x");
    g0_g1x_piH2->SetMarkerStyle(21);
    g0_g1x_piH2->SetMarkerSize(0.8);
    g0_g1x_piH2->GetXaxis()->SetTitleSize(0.05);
	g0_g1x_piH2->GetYaxis()->SetTitleSize(0.05);
	g0_g1x_piH2->GetXaxis()->SetLabelSize(0.05);
	g0_g1x_piH2->GetYaxis()->SetLabelSize(0.05);
    g0_g1x_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g0_g1x_piH2->GetYaxis()->SetTitle("Entries [%]");
    g0_g1x_piH2->GetXaxis()->SetLimits(3750,3950);
    g0_g1x_piH2->GetXaxis()->SetNdivisions(506);
    g0_g1x_piH2->GetYaxis()->SetRangeUser(0,100);
    g0_g1x_piH2->Draw("AP");

    c2->cd(1);
    TGraph *g1_g1x_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g1x_y1_pi_H2[0]) );
    g1_g1x_piH2->SetMarkerColor(kRed);
    g1_g1x_piH2->SetTitle("g1x");
    g1_g1x_piH2->SetMarkerStyle(21);
    g1_g1x_piH2->SetMarkerSize(0.8);
    g1_g1x_piH2->GetXaxis()->SetTitleSize(0.05);
	g1_g1x_piH2->GetYaxis()->SetTitleSize(0.05);
	g1_g1x_piH2->GetXaxis()->SetLabelSize(0.05);
	g1_g1x_piH2->GetYaxis()->SetLabelSize(0.05);
    g1_g1x_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g1_g1x_piH2->GetYaxis()->SetTitle("Entries [%]");
    g1_g1x_piH2->Draw("SAMEP");

	c2->cd(1);
    TGraph *g2_g1x_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g1x_y2_pi_H2[0]) );
    g2_g1x_piH2->SetMarkerColor(kGreen);
    g2_g1x_piH2->SetTitle("g1x");
    g2_g1x_piH2->SetMarkerStyle(21);
    g2_g1x_piH2->SetMarkerSize(0.8);
    g2_g1x_piH2->GetXaxis()->SetTitleSize(0.05);
	g2_g1x_piH2->GetYaxis()->SetTitleSize(0.05);
	g2_g1x_piH2->GetXaxis()->SetLabelSize(0.05);
	g2_g1x_piH2->GetYaxis()->SetLabelSize(0.05);
    g2_g1x_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g2_g1x_piH2->GetYaxis()->SetTitle("Entries [%]");
    g2_g1x_piH2->Draw("SAMEP");

    c2->cd(1);
    TGraph *g3_g1x_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g1x_y3_pi_H2[0]) );
    g3_g1x_piH2->SetMarkerColor(kBlue);
    g3_g1x_piH2->SetTitle("g1x");
    g3_g1x_piH2->SetMarkerStyle(21);
    g3_g1x_piH2->SetMarkerSize(0.8);
    g3_g1x_piH2->GetXaxis()->SetTitleSize(0.05);
	g3_g1x_piH2->GetYaxis()->SetTitleSize(0.05);
	g3_g1x_piH2->GetXaxis()->SetLabelSize(0.05);
	g3_g1x_piH2->GetYaxis()->SetLabelSize(0.05);
    g3_g1x_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g3_g1x_piH2->GetYaxis()->SetTitle("Entries [%]");
    g3_g1x_piH2->Draw("SAMEP");

    c2->cd(1);
    TGraph *g4_g1x_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g1x_y4_pi_H2[0]) );
    g4_g1x_piH2->SetMarkerColor(kMagenta);
    g4_g1x_piH2->SetTitle("g1x");
    g4_g1x_piH2->SetMarkerStyle(21);
    g4_g1x_piH2->SetMarkerSize(0.8);
    g4_g1x_piH2->GetXaxis()->SetTitleSize(0.05);
	g4_g1x_piH2->GetYaxis()->SetTitleSize(0.05);
	g4_g1x_piH2->GetXaxis()->SetLabelSize(0.05);
	g4_g1x_piH2->GetYaxis()->SetLabelSize(0.05);
    g4_g1x_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g4_g1x_piH2->GetYaxis()->SetTitle("Entries [%]");
    g4_g1x_piH2->Draw("SAMEP");

    c2->cd(1);
    TGraph *g5_g1x_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g1x_y5_pi_H2[0]) );
    g5_g1x_piH2->SetMarkerColor(kCyan);
    g5_g1x_piH2->SetTitle("g1x");
    g5_g1x_piH2->SetMarkerStyle(21);
    g5_g1x_piH2->SetMarkerSize(0.8);
    g5_g1x_piH2->GetXaxis()->SetTitleSize(0.05);
	g5_g1x_piH2->GetYaxis()->SetTitleSize(0.05);
	g5_g1x_piH2->GetXaxis()->SetLabelSize(0.05);
	g5_g1x_piH2->GetYaxis()->SetLabelSize(0.05);
    g5_g1x_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g5_g1x_piH2->GetYaxis()->SetTitle("Entries [%]");
    g5_g1x_piH2->Draw("SAMEP");    
    //==========================end: TGraphs for g1x at H2=============================================================================


    //==========================TGraphs for g1y at H2==================================================================================
    c2->cd(2);

	c2->cd(2)->SetGridy(10);

    TGraph *g0_g1y_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g1y_y0_pi_H2[0]) );
    g0_g1y_piH2->SetMarkerColor(kBlack);
    g0_g1y_piH2->SetTitle("g1y");
    g0_g1y_piH2->SetMarkerStyle(21);
    g0_g1y_piH2->SetMarkerSize(0.8);
    g0_g1y_piH2->GetXaxis()->SetTitleSize(0.05);
	g0_g1y_piH2->GetYaxis()->SetTitleSize(0.05);
	g0_g1y_piH2->GetXaxis()->SetLabelSize(0.05);
	g0_g1y_piH2->GetYaxis()->SetLabelSize(0.05);
    g0_g1y_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g0_g1y_piH2->GetYaxis()->SetTitle("Entries [%]");
    g0_g1y_piH2->GetXaxis()->SetLimits(3750,3950);
    g0_g1y_piH2->GetXaxis()->SetNdivisions(506);
    g0_g1y_piH2->GetYaxis()->SetRangeUser(0,100);
    g0_g1y_piH2->Draw("AP");

    c2->cd(2);
    TGraph *g1_g1y_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g1y_y1_pi_H2[0]) );
    g1_g1y_piH2->SetMarkerColor(kRed);
    g1_g1y_piH2->SetTitle("g1y");
    g1_g1y_piH2->SetMarkerStyle(21);
    g1_g1y_piH2->SetMarkerSize(0.8);
    g1_g1y_piH2->GetXaxis()->SetTitleSize(0.05);
	g1_g1y_piH2->GetYaxis()->SetTitleSize(0.05);
	g1_g1y_piH2->GetXaxis()->SetLabelSize(0.05);
	g1_g1y_piH2->GetYaxis()->SetLabelSize(0.05);
    g1_g1y_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g1_g1y_piH2->GetYaxis()->SetTitle("Entries [%]");
    g1_g1y_piH2->Draw("SAMEP");

	c2->cd(2);
    TGraph *g2_g1y_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g1y_y2_pi_H2[0]) );
    g2_g1y_piH2->SetMarkerColor(kGreen);
    g2_g1y_piH2->SetTitle("g1y");
    g2_g1y_piH2->SetMarkerStyle(21);
    g2_g1y_piH2->SetMarkerSize(0.8);
    g2_g1y_piH2->GetXaxis()->SetTitleSize(0.05);
	g2_g1y_piH2->GetYaxis()->SetTitleSize(0.05);
	g2_g1y_piH2->GetXaxis()->SetLabelSize(0.05);
	g2_g1y_piH2->GetYaxis()->SetLabelSize(0.05);
    g2_g1y_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g2_g1y_piH2->GetYaxis()->SetTitle("Entries [%]");
    g2_g1y_piH2->Draw("SAMEP");

    c2->cd(2);
    TGraph *g3_g1y_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g1y_y3_pi_H2[0]) );
    g3_g1y_piH2->SetMarkerColor(kBlue);
    g3_g1y_piH2->SetTitle("g1y");
    g3_g1y_piH2->SetMarkerStyle(21);
    g3_g1y_piH2->SetMarkerSize(0.8);
    g3_g1y_piH2->GetXaxis()->SetTitleSize(0.05);
	g3_g1y_piH2->GetYaxis()->SetTitleSize(0.05);
	g3_g1y_piH2->GetXaxis()->SetLabelSize(0.05);
	g3_g1y_piH2->GetYaxis()->SetLabelSize(0.05);
    g3_g1y_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g3_g1y_piH2->GetYaxis()->SetTitle("Entries [%]");
    g3_g1y_piH2->Draw("SAMEP");

    c2->cd(2);
    TGraph *g4_g1y_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g1y_y4_pi_H2[0]) );
    g4_g1y_piH2->SetMarkerColor(kMagenta);
    g4_g1y_piH2->SetTitle("g1y");
    g4_g1y_piH2->SetMarkerStyle(21);
    g4_g1y_piH2->SetMarkerSize(0.8);
    g4_g1y_piH2->GetXaxis()->SetTitleSize(0.05);
	g4_g1y_piH2->GetYaxis()->SetTitleSize(0.05);
	g4_g1y_piH2->GetXaxis()->SetLabelSize(0.05);
	g4_g1y_piH2->GetYaxis()->SetLabelSize(0.05);
    g4_g1y_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g4_g1y_piH2->GetYaxis()->SetTitle("Entries [%]");
    g4_g1y_piH2->Draw("SAMEP");

    c2->cd(2);
    TGraph *g5_g1y_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g1y_y5_pi_H2[0]) );
    g5_g1y_piH2->SetMarkerColor(kCyan);
    g5_g1y_piH2->SetTitle("g1y");
    g5_g1y_piH2->SetMarkerStyle(21);
    g5_g1y_piH2->SetMarkerSize(0.8);
    g5_g1y_piH2->GetXaxis()->SetTitleSize(0.05);
	g5_g1y_piH2->GetYaxis()->SetTitleSize(0.05);
	g5_g1y_piH2->GetXaxis()->SetLabelSize(0.05);
	g5_g1y_piH2->GetYaxis()->SetLabelSize(0.05);
    g5_g1y_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g5_g1y_piH2->GetYaxis()->SetTitle("Entries [%]");
    g5_g1y_piH2->Draw("SAMEP");    
    //==========================end: TGraphs for g1y at H2=============================================================================


    //==========================TGraphs for g2x at H2==================================================================================
    c2->cd(3);

	c2->cd(3)->SetGridy(10);

    TGraph *g0_g2x_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g2x_y0_pi_H2[0]) );
    g0_g2x_piH2->SetMarkerColor(kBlack);
    g0_g2x_piH2->SetTitle("g2x");
    g0_g2x_piH2->SetMarkerStyle(21);
    g0_g2x_piH2->SetMarkerSize(0.8);
    g0_g2x_piH2->GetXaxis()->SetTitleSize(0.05);
	g0_g2x_piH2->GetYaxis()->SetTitleSize(0.05);
	g0_g2x_piH2->GetXaxis()->SetLabelSize(0.05);
	g0_g2x_piH2->GetYaxis()->SetLabelSize(0.05);
    g0_g2x_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g0_g2x_piH2->GetYaxis()->SetTitle("Entries [%]");
    g0_g2x_piH2->GetXaxis()->SetLimits(3750,3950);
    g0_g2x_piH2->GetXaxis()->SetNdivisions(506);
    g0_g2x_piH2->GetYaxis()->SetRangeUser(0,100);
    g0_g2x_piH2->Draw("AP");

    c2->cd(3);
    TGraph *g1_g2x_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g2x_y1_pi_H2[0]) );
    g1_g2x_piH2->SetMarkerColor(kRed);
    g1_g2x_piH2->SetTitle("g2x");
    g1_g2x_piH2->SetMarkerStyle(21);
    g1_g2x_piH2->SetMarkerSize(0.8);
    g1_g2x_piH2->GetXaxis()->SetTitleSize(0.05);
	g1_g2x_piH2->GetYaxis()->SetTitleSize(0.05);
	g1_g2x_piH2->GetXaxis()->SetLabelSize(0.05);
	g1_g2x_piH2->GetYaxis()->SetLabelSize(0.05);
    g1_g2x_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g1_g2x_piH2->GetYaxis()->SetTitle("Entries [%]");
    g1_g2x_piH2->Draw("SAMEP");

	c2->cd(3);
    TGraph *g2_g2x_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g2x_y2_pi_H2[0]) );
    g2_g2x_piH2->SetMarkerColor(kGreen);
    g2_g2x_piH2->SetTitle("g2x");
    g2_g2x_piH2->SetMarkerStyle(21);
    g2_g2x_piH2->SetMarkerSize(0.8);
    g2_g2x_piH2->GetXaxis()->SetTitleSize(0.05);
	g2_g2x_piH2->GetYaxis()->SetTitleSize(0.05);
	g2_g2x_piH2->GetXaxis()->SetLabelSize(0.05);
	g2_g2x_piH2->GetYaxis()->SetLabelSize(0.05);
    g2_g2x_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g2_g2x_piH2->GetYaxis()->SetTitle("Entries [%]");
    g2_g2x_piH2->Draw("SAMEP");

    c2->cd(3);
    TGraph *g3_g2x_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g2x_y3_pi_H2[0]) );
    g3_g2x_piH2->SetMarkerColor(kBlue);
    g3_g2x_piH2->SetTitle("g2x");
    g3_g2x_piH2->SetMarkerStyle(21);
    g3_g2x_piH2->SetMarkerSize(0.8);
    g3_g2x_piH2->GetXaxis()->SetTitleSize(0.05);
	g3_g2x_piH2->GetYaxis()->SetTitleSize(0.05);
	g3_g2x_piH2->GetXaxis()->SetLabelSize(0.05);
	g3_g2x_piH2->GetYaxis()->SetLabelSize(0.05);
    g3_g2x_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g3_g2x_piH2->GetYaxis()->SetTitle("Entries [%]");
    g3_g2x_piH2->Draw("SAMEP");

    c2->cd(3);
    TGraph *g4_g2x_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g2x_y4_pi_H2[0]) );
    g4_g2x_piH2->SetMarkerColor(kMagenta);
    g4_g2x_piH2->SetTitle("g2x");
    g4_g2x_piH2->SetMarkerStyle(21);
    g4_g2x_piH2->SetMarkerSize(0.8);
    g4_g2x_piH2->GetXaxis()->SetTitleSize(0.05);
	g4_g2x_piH2->GetYaxis()->SetTitleSize(0.05);
	g4_g2x_piH2->GetXaxis()->SetLabelSize(0.05);
	g4_g2x_piH2->GetYaxis()->SetLabelSize(0.05);
    g4_g2x_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g4_g2x_piH2->GetYaxis()->SetTitle("Entries [%]");
    g4_g2x_piH2->Draw("SAMEP");

    c2->cd(3);
    TGraph *g5_g2x_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g2x_y5_pi_H2[0]) );
    g5_g2x_piH2->SetMarkerColor(kCyan);
    g5_g2x_piH2->SetTitle("g2x");
    g5_g2x_piH2->SetMarkerStyle(21);
    g5_g2x_piH2->SetMarkerSize(0.8);
    g5_g2x_piH2->GetXaxis()->SetTitleSize(0.05);
	g5_g2x_piH2->GetYaxis()->SetTitleSize(0.05);
	g5_g2x_piH2->GetXaxis()->SetLabelSize(0.05);
	g5_g2x_piH2->GetYaxis()->SetLabelSize(0.05);
    g5_g2x_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g5_g2x_piH2->GetYaxis()->SetTitle("Entries [%]");
    g5_g2x_piH2->Draw("SAMEP");    
    //==========================end: TGraphs for g2x at H2=============================================================================

    //==========================TGraphs for g2y at H2==================================================================================
    c2->cd(4);

	c2->cd(4)->SetGridy(10);

    TGraph *g0_g2y_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g2y_y0_pi_H2[0]) );
    g0_g2y_piH2->SetMarkerColor(kBlack);
    g0_g2y_piH2->SetTitle("g2y");
    g0_g2y_piH2->SetMarkerStyle(21);
    g0_g2y_piH2->SetMarkerSize(0.8);
    g0_g2y_piH2->GetXaxis()->SetTitleSize(0.05);
	g0_g2y_piH2->GetYaxis()->SetTitleSize(0.05);
	g0_g2y_piH2->GetXaxis()->SetLabelSize(0.05);
	g0_g2y_piH2->GetYaxis()->SetLabelSize(0.05);
    g0_g2y_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g0_g2y_piH2->GetYaxis()->SetTitle("Entries [%]");
    g0_g2y_piH2->GetXaxis()->SetLimits(3750,3950);
    g0_g2y_piH2->GetXaxis()->SetNdivisions(506);
    g0_g2y_piH2->GetYaxis()->SetRangeUser(0,100);
    g0_g2y_piH2->Draw("AP");

    c2->cd(4);
    TGraph *g1_g2y_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g2y_y1_pi_H2[0]) );
    g1_g2y_piH2->SetMarkerColor(kRed);
    g1_g2y_piH2->SetTitle("g2y");
    g1_g2y_piH2->SetMarkerStyle(21);
    g1_g2y_piH2->SetMarkerSize(0.8);
    g1_g2y_piH2->GetXaxis()->SetTitleSize(0.05);
	g1_g2y_piH2->GetYaxis()->SetTitleSize(0.05);
	g1_g2y_piH2->GetXaxis()->SetLabelSize(0.05);
	g1_g2y_piH2->GetYaxis()->SetLabelSize(0.05);
    g1_g2y_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g1_g2y_piH2->GetYaxis()->SetTitle("Entries [%]");
    g1_g2y_piH2->Draw("SAMEP");

	c2->cd(4);
    TGraph *g2_g2y_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g2y_y2_pi_H2[0]) );
    g2_g2y_piH2->SetMarkerColor(kGreen);
    g2_g2y_piH2->SetTitle("g2y");
    g2_g2y_piH2->SetMarkerStyle(21);
    g2_g2y_piH2->SetMarkerSize(0.8);
    g2_g2y_piH2->GetXaxis()->SetTitleSize(0.05);
	g2_g2y_piH2->GetYaxis()->SetTitleSize(0.05);
	g2_g2y_piH2->GetXaxis()->SetLabelSize(0.05);
	g2_g2y_piH2->GetYaxis()->SetLabelSize(0.05);
    g2_g2y_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g2_g2y_piH2->GetYaxis()->SetTitle("Entries [%]");
    g2_g2y_piH2->Draw("SAMEP");

    c2->cd(4);
    TGraph *g3_g2y_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g2y_y3_pi_H2[0]) );
    g3_g2y_piH2->SetMarkerColor(kBlue);
    g3_g2y_piH2->SetTitle("g2y");
    g3_g2y_piH2->SetMarkerStyle(21);
    g3_g2y_piH2->SetMarkerSize(0.8);
    g3_g2y_piH2->GetXaxis()->SetTitleSize(0.05);
	g3_g2y_piH2->GetYaxis()->SetTitleSize(0.05);
	g3_g2y_piH2->GetXaxis()->SetLabelSize(0.05);
	g3_g2y_piH2->GetYaxis()->SetLabelSize(0.05);
    g3_g2y_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g3_g2y_piH2->GetYaxis()->SetTitle("Entries [%]");
    g3_g2y_piH2->Draw("SAMEP");

    c2->cd(4);
    TGraph *g4_g2y_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g2y_y4_pi_H2[0]) );
    g4_g2y_piH2->SetMarkerColor(kMagenta);
    g4_g2y_piH2->SetTitle("g2y");
    g4_g2y_piH2->SetMarkerStyle(21);
    g4_g2y_piH2->SetMarkerSize(0.8);
    g4_g2y_piH2->GetXaxis()->SetTitleSize(0.05);
	g4_g2y_piH2->GetYaxis()->SetTitleSize(0.05);
	g4_g2y_piH2->GetXaxis()->SetLabelSize(0.05);
	g4_g2y_piH2->GetYaxis()->SetLabelSize(0.05);
    g4_g2y_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g4_g2y_piH2->GetYaxis()->SetTitle("Entries [%]");
    g4_g2y_piH2->Draw("SAMEP");

    c2->cd(4);
    TGraph *g5_g2y_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g2y_y5_pi_H2[0]) );
    g5_g2y_piH2->SetMarkerColor(kCyan);
    g5_g2y_piH2->SetTitle("g2y");
    g5_g2y_piH2->SetMarkerStyle(21);
    g5_g2y_piH2->SetMarkerSize(0.8);
    g5_g2y_piH2->GetXaxis()->SetTitleSize(0.05);
	g5_g2y_piH2->GetYaxis()->SetTitleSize(0.05);
	g5_g2y_piH2->GetXaxis()->SetLabelSize(0.05);
	g5_g2y_piH2->GetYaxis()->SetLabelSize(0.05);
    g5_g2y_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g5_g2y_piH2->GetYaxis()->SetTitle("Entries [%]");
    g5_g2y_piH2->Draw("SAMEP");    
    //==========================end: TGraphs for g2y at H2=============================================================================

    //==========================TGraphs for g3x at H2==================================================================================
    c2->cd(5);

	c2->cd(5)->SetGridy(10);

    TGraph *g0_g3x_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g3x_y0_pi_H2[0]) );
    g0_g3x_piH2->SetMarkerColor(kBlack);
    g0_g3x_piH2->SetTitle("g3x");
    g0_g3x_piH2->SetMarkerStyle(21);
    g0_g3x_piH2->SetMarkerSize(0.8);
    g0_g3x_piH2->GetXaxis()->SetTitleSize(0.05);
	g0_g3x_piH2->GetYaxis()->SetTitleSize(0.05);
	g0_g3x_piH2->GetXaxis()->SetLabelSize(0.05);
	g0_g3x_piH2->GetYaxis()->SetLabelSize(0.05);
    g0_g3x_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g0_g3x_piH2->GetYaxis()->SetTitle("Entries [%]");
    g0_g3x_piH2->GetXaxis()->SetLimits(3750,3950);
    g0_g3x_piH2->GetXaxis()->SetNdivisions(506);
    g0_g3x_piH2->GetYaxis()->SetRangeUser(0,100);
    g0_g3x_piH2->Draw("AP");

    c2->cd(5);
    TGraph *g1_g3x_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g3x_y1_pi_H2[0]) );
    g1_g3x_piH2->SetMarkerColor(kRed);
    g1_g3x_piH2->SetTitle("g3x");
    g1_g3x_piH2->SetMarkerStyle(21);
    g1_g3x_piH2->SetMarkerSize(0.8);
    g1_g3x_piH2->GetXaxis()->SetTitleSize(0.05);
	g1_g3x_piH2->GetYaxis()->SetTitleSize(0.05);
	g1_g3x_piH2->GetXaxis()->SetLabelSize(0.05);
	g1_g3x_piH2->GetYaxis()->SetLabelSize(0.05);
    g1_g3x_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g1_g3x_piH2->GetYaxis()->SetTitle("Entries [%]");
    g1_g3x_piH2->Draw("SAMEP");

	c2->cd(5);
    TGraph *g2_g3x_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g3x_y2_pi_H2[0]) );
    g2_g3x_piH2->SetMarkerColor(kGreen);
    g2_g3x_piH2->SetTitle("g3x");
    g2_g3x_piH2->SetMarkerStyle(21);
    g2_g3x_piH2->SetMarkerSize(0.8);
    g2_g3x_piH2->GetXaxis()->SetTitleSize(0.05);
	g2_g3x_piH2->GetYaxis()->SetTitleSize(0.05);
	g2_g3x_piH2->GetXaxis()->SetLabelSize(0.05);
	g2_g3x_piH2->GetYaxis()->SetLabelSize(0.05);
    g2_g3x_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g2_g3x_piH2->GetYaxis()->SetTitle("Entries [%]");
    g2_g3x_piH2->Draw("SAMEP");

    c2->cd(5);
    TGraph *g3_g3x_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g3x_y3_pi_H2[0]) );
    g3_g3x_piH2->SetMarkerColor(kBlue);
    g3_g3x_piH2->SetTitle("g3x");
    g3_g3x_piH2->SetMarkerStyle(21);
    g3_g3x_piH2->SetMarkerSize(0.8);
    g3_g3x_piH2->GetXaxis()->SetTitleSize(0.05);
	g3_g3x_piH2->GetYaxis()->SetTitleSize(0.05);
	g3_g3x_piH2->GetXaxis()->SetLabelSize(0.05);
	g3_g3x_piH2->GetYaxis()->SetLabelSize(0.05);
    g3_g3x_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g3_g3x_piH2->GetYaxis()->SetTitle("Entries [%]");
    g3_g3x_piH2->Draw("SAMEP");

    c2->cd(5);
    TGraph *g4_g3x_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g3x_y4_pi_H2[0]) );
    g4_g3x_piH2->SetMarkerColor(kMagenta);
    g4_g3x_piH2->SetTitle("g3x");
    g4_g3x_piH2->SetMarkerStyle(21);
    g4_g3x_piH2->SetMarkerSize(0.8);
    g4_g3x_piH2->GetXaxis()->SetTitleSize(0.05);
	g4_g3x_piH2->GetYaxis()->SetTitleSize(0.05);
	g4_g3x_piH2->GetXaxis()->SetLabelSize(0.05);
	g4_g3x_piH2->GetYaxis()->SetLabelSize(0.05);
    g4_g3x_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g4_g3x_piH2->GetYaxis()->SetTitle("Entries [%]");
    g4_g3x_piH2->Draw("SAMEP");

    c2->cd(5);
    TGraph *g5_g3x_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g3x_y5_pi_H2[0]) );
    g5_g3x_piH2->SetMarkerColor(kCyan);
    g5_g3x_piH2->SetTitle("g3x");
    g5_g3x_piH2->SetMarkerStyle(21);
    g5_g3x_piH2->SetMarkerSize(0.8);
    g5_g3x_piH2->GetXaxis()->SetTitleSize(0.05);
	g5_g3x_piH2->GetYaxis()->SetTitleSize(0.05);
	g5_g3x_piH2->GetXaxis()->SetLabelSize(0.05);
	g5_g3x_piH2->GetYaxis()->SetLabelSize(0.05);
    g5_g3x_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g5_g3x_piH2->GetYaxis()->SetTitle("Entries [%]");
    g5_g3x_piH2->Draw("SAMEP");    
    //==========================end: TGraphs for g3x at H2=============================================================================


    //==========================TGraphs for g3y at H2==================================================================================
    c2->cd(6);

	c2->cd(6)->SetGridy(10);

    TGraph *g0_g3y_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g3y_y0_pi_H2[0]) );
    g0_g3y_piH2->SetMarkerColor(kBlack);
    g0_g3y_piH2->SetTitle("g3y");
    g0_g3y_piH2->SetMarkerStyle(21);
    g0_g3y_piH2->SetMarkerSize(0.8);
    g0_g3y_piH2->GetXaxis()->SetTitleSize(0.05);
	g0_g3y_piH2->GetYaxis()->SetTitleSize(0.05);
	g0_g3y_piH2->GetXaxis()->SetLabelSize(0.05);
	g0_g3y_piH2->GetYaxis()->SetLabelSize(0.05);
    g0_g3y_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g0_g3y_piH2->GetYaxis()->SetTitle("Entries [%]");
    g0_g3y_piH2->GetXaxis()->SetLimits(3750,3950);
    g0_g3y_piH2->GetXaxis()->SetNdivisions(506);
    g0_g3y_piH2->GetYaxis()->SetRangeUser(0,100);
    g0_g3y_piH2->Draw("AP");

    c2->cd(6);
    TGraph *g1_g3y_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g3y_y1_pi_H2[0]) );
    g1_g3y_piH2->SetMarkerColor(kRed);
    g1_g3y_piH2->SetTitle("g3y");
    g1_g3y_piH2->SetMarkerStyle(21);
    g1_g3y_piH2->SetMarkerSize(0.8);
    g1_g3y_piH2->GetXaxis()->SetTitleSize(0.05);
	g1_g3y_piH2->GetYaxis()->SetTitleSize(0.05);
	g1_g3y_piH2->GetXaxis()->SetLabelSize(0.05);
	g1_g3y_piH2->GetYaxis()->SetLabelSize(0.05);
    g1_g3y_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g1_g3y_piH2->GetYaxis()->SetTitle("Entries [%]");
    g1_g3y_piH2->Draw("SAMEP");

	c2->cd(6);
    TGraph *g2_g3y_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g3y_y2_pi_H2[0]) );
    g2_g3y_piH2->SetMarkerColor(kGreen);
    g2_g3y_piH2->SetTitle("g3y");
    g2_g3y_piH2->SetMarkerStyle(21);
    g2_g3y_piH2->SetMarkerSize(0.8);
    g2_g3y_piH2->GetXaxis()->SetTitleSize(0.05);
	g2_g3y_piH2->GetYaxis()->SetTitleSize(0.05);
	g2_g3y_piH2->GetXaxis()->SetLabelSize(0.05);
	g2_g3y_piH2->GetYaxis()->SetLabelSize(0.05);
    g2_g3y_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g2_g3y_piH2->GetYaxis()->SetTitle("Entries [%]");
    g2_g3y_piH2->Draw("SAMEP");

    c2->cd(6);
    TGraph *g3_g3y_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g3y_y3_pi_H2[0]) );
    g3_g3y_piH2->SetMarkerColor(kBlue);
    g3_g3y_piH2->SetTitle("g3y");
    g3_g3y_piH2->SetMarkerStyle(21);
    g3_g3y_piH2->SetMarkerSize(0.8);
    g3_g3y_piH2->GetXaxis()->SetTitleSize(0.05);
	g3_g3y_piH2->GetYaxis()->SetTitleSize(0.05);
	g3_g3y_piH2->GetXaxis()->SetLabelSize(0.05);
	g3_g3y_piH2->GetYaxis()->SetLabelSize(0.05);
    g3_g3y_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g3_g3y_piH2->GetYaxis()->SetTitle("Entries [%]");
    g3_g3y_piH2->Draw("SAMEP");

    c2->cd(6);
    TGraph *g4_g3y_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g3y_y4_pi_H2[0]) );
    g4_g3y_piH2->SetMarkerColor(kMagenta);
    g4_g3y_piH2->SetTitle("g3y");
    g4_g3y_piH2->SetMarkerStyle(21);
    g4_g3y_piH2->SetMarkerSize(0.8);
    g4_g3y_piH2->GetXaxis()->SetTitleSize(0.05);
	g4_g3y_piH2->GetYaxis()->SetTitleSize(0.05);
	g4_g3y_piH2->GetXaxis()->SetLabelSize(0.05);
	g4_g3y_piH2->GetYaxis()->SetLabelSize(0.05);
    g4_g3y_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g4_g3y_piH2->GetYaxis()->SetTitle("Entries [%]");
    g4_g3y_piH2->Draw("SAMEP");

    c2->cd(6);
    TGraph *g5_g3y_piH2 = new TGraph ( x_pi_H2.size() , &(x_pi_H2[0]) , &(g3y_y5_pi_H2[0]) );
    g5_g3y_piH2->SetMarkerColor(kCyan);
    g5_g3y_piH2->SetTitle("g3y");
    g5_g3y_piH2->SetMarkerStyle(21);
    g5_g3y_piH2->SetMarkerSize(0.8);
    g5_g3y_piH2->GetXaxis()->SetTitleSize(0.05);
	g5_g3y_piH2->GetYaxis()->SetTitleSize(0.05);
	g5_g3y_piH2->GetXaxis()->SetLabelSize(0.05);
	g5_g3y_piH2->GetYaxis()->SetLabelSize(0.05);
    g5_g3y_piH2->GetXaxis()->SetTitle("Voltage [V]");
    g5_g3y_piH2->GetYaxis()->SetTitle("Entries [%]");
    g5_g3y_piH2->Draw("SAMEP");    
    //==========================end: TGraphs for g3y at H2=============================================================================

    canv2->cd();
    TPad *newpad2 = new TPad("newpad","a transparent pad",0,0,1,1);
	newpad2->SetFillStyle(4000);
	newpad2->Draw();
	newpad2->cd();
	TPaveLabel *title2 = new TPaveLabel (0.01,0.94,0.3,0.98,H2pititle);
	title2->SetFillColor(kWhite);
	title2->Draw();
    TLegend *leg2 = new TLegend(0.515, 0.92, 0.96, 0.995);
	leg2->SetFillColor(0);
	leg2-> SetNColumns(2);
	//leg2->SetTextFont(62);
	leg2->SetTextSize(0.02);
	//leg2->SetHeader("");
	leg2->AddEntry(g0_g1x_piH2, "Fraction of events with 0 Clusters", "p");
	leg2->AddEntry(g1_g1x_piH2, "Fraction of events with 1 Clusters", "p");
	leg2->AddEntry(g2_g1x_piH2, "Fraction of events with 2 Clusters", "p");
	leg2->AddEntry(g3_g1x_piH2, "Fraction of events with 3 Clusters", "p");
	leg2->AddEntry(g4_g1x_piH2, "Fraction of events with 4 Clusters", "p");
	leg2->AddEntry(g5_g1x_piH2, "Fraction of events with 5 Clusters", "p");
	leg2->Draw();
//===========================================END: draw canvas for PION runs at H2======================================================================================





//===========================================START: draw canvas for MUON runs at H4======================================================================================
    //==========================TGraphs for g1x at H4==================================================================================
    c3->cd(1);

	c3->cd(1)->SetGridy(10);

    TGraph *g0_g1x_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g1x_y0_mu_H4[0]) );
    g0_g1x_muH4->SetMarkerColor(kBlack);
    g0_g1x_muH4->SetTitle("g1x");
    g0_g1x_muH4->SetMarkerStyle(21);
    g0_g1x_muH4->SetMarkerSize(0.8);
    g0_g1x_muH4->GetXaxis()->SetTitleSize(0.05);
	g0_g1x_muH4->GetYaxis()->SetTitleSize(0.05);
	g0_g1x_muH4->GetXaxis()->SetLabelSize(0.05);
	g0_g1x_muH4->GetYaxis()->SetLabelSize(0.05);
    g0_g1x_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g0_g1x_muH4->GetYaxis()->SetTitle("Entries [%]");
    g0_g1x_muH4->GetXaxis()->SetLimits(4190,4390);
    g0_g1x_muH4->GetXaxis()->SetNdivisions(506);
    g0_g1x_muH4->GetYaxis()->SetRangeUser(0,100);
    g0_g1x_muH4->Draw("AP");

    c3->cd(1);
    TGraph *g1_g1x_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g1x_y1_mu_H4[0]) );
    g1_g1x_muH4->SetMarkerColor(kRed);
    g1_g1x_muH4->SetTitle("g1x");
    g1_g1x_muH4->SetMarkerStyle(21);
    g1_g1x_muH4->SetMarkerSize(0.8);
    g1_g1x_muH4->GetXaxis()->SetTitleSize(0.05);
	g1_g1x_muH4->GetYaxis()->SetTitleSize(0.05);
	g1_g1x_muH4->GetXaxis()->SetLabelSize(0.05);
	g1_g1x_muH4->GetYaxis()->SetLabelSize(0.05);
    g1_g1x_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g1_g1x_muH4->GetYaxis()->SetTitle("Entries [%]");
    g1_g1x_muH4->Draw("SAMEP");

	c3->cd(1);
    TGraph *g2_g1x_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g1x_y2_mu_H4[0]) );
    g2_g1x_muH4->SetMarkerColor(kGreen);
    g2_g1x_muH4->SetTitle("g1x");
    g2_g1x_muH4->SetMarkerStyle(21);
    g2_g1x_muH4->SetMarkerSize(0.8);
    g2_g1x_muH4->GetXaxis()->SetTitleSize(0.05);
	g2_g1x_muH4->GetYaxis()->SetTitleSize(0.05);
	g2_g1x_muH4->GetXaxis()->SetLabelSize(0.05);
	g2_g1x_muH4->GetYaxis()->SetLabelSize(0.05);
    g2_g1x_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g2_g1x_muH4->GetYaxis()->SetTitle("Entries [%]");
    g2_g1x_muH4->Draw("SAMEP");

    c3->cd(1);
    TGraph *g3_g1x_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g1x_y3_mu_H4[0]) );
    g3_g1x_muH4->SetMarkerColor(kBlue);
    g3_g1x_muH4->SetTitle("g1x");
    g3_g1x_muH4->SetMarkerStyle(21);
    g3_g1x_muH4->SetMarkerSize(0.8);
    g3_g1x_muH4->GetXaxis()->SetTitleSize(0.05);
	g3_g1x_muH4->GetYaxis()->SetTitleSize(0.05);
	g3_g1x_muH4->GetXaxis()->SetLabelSize(0.05);
	g3_g1x_muH4->GetYaxis()->SetLabelSize(0.05);
    g3_g1x_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g3_g1x_muH4->GetYaxis()->SetTitle("Entries [%]");
    g3_g1x_muH4->Draw("SAMEP");

    c3->cd(1);
    TGraph *g4_g1x_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g1x_y4_mu_H4[0]) );
    g4_g1x_muH4->SetMarkerColor(kMagenta);
    g4_g1x_muH4->SetTitle("g1x");
    g4_g1x_muH4->SetMarkerStyle(21);
    g4_g1x_muH4->SetMarkerSize(0.8);
    g4_g1x_muH4->GetXaxis()->SetTitleSize(0.05);
	g4_g1x_muH4->GetYaxis()->SetTitleSize(0.05);
	g4_g1x_muH4->GetXaxis()->SetLabelSize(0.05);
	g4_g1x_muH4->GetYaxis()->SetLabelSize(0.05);
    g4_g1x_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g4_g1x_muH4->GetYaxis()->SetTitle("Entries [%]");
    g4_g1x_muH4->Draw("SAMEP");

    c3->cd(1);
    TGraph *g5_g1x_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g1x_y5_mu_H4[0]) );
    g5_g1x_muH4->SetMarkerColor(kCyan);
    g5_g1x_muH4->SetTitle("g1x");
    g5_g1x_muH4->SetMarkerStyle(21);
    g5_g1x_muH4->SetMarkerSize(0.8);
    g5_g1x_muH4->GetXaxis()->SetTitleSize(0.05);
	g5_g1x_muH4->GetYaxis()->SetTitleSize(0.05);
	g5_g1x_muH4->GetXaxis()->SetLabelSize(0.05);
	g5_g1x_muH4->GetYaxis()->SetLabelSize(0.05);
    g5_g1x_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g5_g1x_muH4->GetYaxis()->SetTitle("Entries [%]");
    g5_g1x_muH4->Draw("SAMEP");    
    //==========================end: TGraphs for g1x at H4=============================================================================


    //==========================TGraphs for g1y at H4==================================================================================
    c3->cd(2);

	c3->cd(2)->SetGridy(10);

    TGraph *g0_g1y_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g1y_y0_mu_H4[0]) );
    g0_g1y_muH4->SetMarkerColor(kBlack);
    g0_g1y_muH4->SetTitle("g1y");
    g0_g1y_muH4->SetMarkerStyle(21);
    g0_g1y_muH4->SetMarkerSize(0.8);
    g0_g1y_muH4->GetXaxis()->SetTitleSize(0.05);
	g0_g1y_muH4->GetYaxis()->SetTitleSize(0.05);
	g0_g1y_muH4->GetXaxis()->SetLabelSize(0.05);
	g0_g1y_muH4->GetYaxis()->SetLabelSize(0.05);
    g0_g1y_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g0_g1y_muH4->GetYaxis()->SetTitle("Entries [%]");
    g0_g1y_muH4->GetXaxis()->SetLimits(4190,4390);
    g0_g1y_muH4->GetXaxis()->SetNdivisions(506);
    g0_g1y_muH4->GetYaxis()->SetRangeUser(0,100);
    g0_g1y_muH4->Draw("AP");

    c3->cd(2);
    TGraph *g1_g1y_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g1y_y1_mu_H4[0]) );
    g1_g1y_muH4->SetMarkerColor(kRed);
    g1_g1y_muH4->SetTitle("g1y");
    g1_g1y_muH4->SetMarkerStyle(21);
    g1_g1y_muH4->SetMarkerSize(0.8);
    g1_g1y_muH4->GetXaxis()->SetTitleSize(0.05);
	g1_g1y_muH4->GetYaxis()->SetTitleSize(0.05);
	g1_g1y_muH4->GetXaxis()->SetLabelSize(0.05);
	g1_g1y_muH4->GetYaxis()->SetLabelSize(0.05);
    g1_g1y_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g1_g1y_muH4->GetYaxis()->SetTitle("Entries [%]");
    g1_g1y_muH4->Draw("SAMEP");

	c3->cd(2);
    TGraph *g2_g1y_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g1y_y2_mu_H4[0]) );
    g2_g1y_muH4->SetMarkerColor(kGreen);
    g2_g1y_muH4->SetTitle("g1y");
    g2_g1y_muH4->SetMarkerStyle(21);
    g2_g1y_muH4->SetMarkerSize(0.8);
    g2_g1y_muH4->GetXaxis()->SetTitleSize(0.05);
	g2_g1y_muH4->GetYaxis()->SetTitleSize(0.05);
	g2_g1y_muH4->GetXaxis()->SetLabelSize(0.05);
	g2_g1y_muH4->GetYaxis()->SetLabelSize(0.05);
    g2_g1y_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g2_g1y_muH4->GetYaxis()->SetTitle("Entries [%]");
    g2_g1y_muH4->Draw("SAMEP");

    c3->cd(2);
    TGraph *g3_g1y_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g1y_y3_mu_H4[0]) );
    g3_g1y_muH4->SetMarkerColor(kBlue);
    g3_g1y_muH4->SetTitle("g1y");
    g3_g1y_muH4->SetMarkerStyle(21);
    g3_g1y_muH4->SetMarkerSize(0.8);
    g3_g1y_muH4->GetXaxis()->SetTitleSize(0.05);
	g3_g1y_muH4->GetYaxis()->SetTitleSize(0.05);
	g3_g1y_muH4->GetXaxis()->SetLabelSize(0.05);
	g3_g1y_muH4->GetYaxis()->SetLabelSize(0.05);
    g3_g1y_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g3_g1y_muH4->GetYaxis()->SetTitle("Entries [%]");
    g3_g1y_muH4->Draw("SAMEP");

    c3->cd(2);
    TGraph *g4_g1y_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g1y_y4_mu_H4[0]) );
    g4_g1y_muH4->SetMarkerColor(kMagenta);
    g4_g1y_muH4->SetTitle("g1y");
    g4_g1y_muH4->SetMarkerStyle(21);
    g4_g1y_muH4->SetMarkerSize(0.8);
    g4_g1y_muH4->GetXaxis()->SetTitleSize(0.05);
	g4_g1y_muH4->GetYaxis()->SetTitleSize(0.05);
	g4_g1y_muH4->GetXaxis()->SetLabelSize(0.05);
	g4_g1y_muH4->GetYaxis()->SetLabelSize(0.05);
    g4_g1y_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g4_g1y_muH4->GetYaxis()->SetTitle("Entries [%]");
    g4_g1y_muH4->Draw("SAMEP");

    c3->cd(2);
    TGraph *g5_g1y_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g1y_y5_mu_H4[0]) );
    g5_g1y_muH4->SetMarkerColor(kCyan);
    g5_g1y_muH4->SetTitle("g1y");
    g5_g1y_muH4->SetMarkerStyle(21);
    g5_g1y_muH4->SetMarkerSize(0.8);
    g5_g1y_muH4->GetXaxis()->SetTitleSize(0.05);
	g5_g1y_muH4->GetYaxis()->SetTitleSize(0.05);
	g5_g1y_muH4->GetXaxis()->SetLabelSize(0.05);
	g5_g1y_muH4->GetYaxis()->SetLabelSize(0.05);
    g5_g1y_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g5_g1y_muH4->GetYaxis()->SetTitle("Entries [%]");
    g5_g1y_muH4->Draw("SAMEP");    
    //==========================end: TGraphs for g1y at H4=============================================================================


    //==========================TGraphs for g2x at H4==================================================================================
    c3->cd(3);

	c3->cd(3)->SetGridy(10);

    TGraph *g0_g2x_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g2x_y0_mu_H4[0]) );
    g0_g2x_muH4->SetMarkerColor(kBlack);
    g0_g2x_muH4->SetTitle("g2x");
    g0_g2x_muH4->SetMarkerStyle(21);
    g0_g2x_muH4->SetMarkerSize(0.8);
    g0_g2x_muH4->GetXaxis()->SetTitleSize(0.05);
	g0_g2x_muH4->GetYaxis()->SetTitleSize(0.05);
	g0_g2x_muH4->GetXaxis()->SetLabelSize(0.05);
	g0_g2x_muH4->GetYaxis()->SetLabelSize(0.05);
    g0_g2x_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g0_g2x_muH4->GetYaxis()->SetTitle("Entries [%]");
    g0_g2x_muH4->GetXaxis()->SetLimits(4190,4390);
    g0_g2x_muH4->GetXaxis()->SetNdivisions(506);
    g0_g2x_muH4->GetYaxis()->SetRangeUser(0,100);
    g0_g2x_muH4->Draw("AP");

    c3->cd(3);
    TGraph *g1_g2x_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g2x_y1_mu_H4[0]) );
    g1_g2x_muH4->SetMarkerColor(kRed);
    g1_g2x_muH4->SetTitle("g2x");
    g1_g2x_muH4->SetMarkerStyle(21);
    g1_g2x_muH4->SetMarkerSize(0.8);
    g1_g2x_muH4->GetXaxis()->SetTitleSize(0.05);
	g1_g2x_muH4->GetYaxis()->SetTitleSize(0.05);
	g1_g2x_muH4->GetXaxis()->SetLabelSize(0.05);
	g1_g2x_muH4->GetYaxis()->SetLabelSize(0.05);
    g1_g2x_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g1_g2x_muH4->GetYaxis()->SetTitle("Entries [%]");
    g1_g2x_muH4->Draw("SAMEP");

	c3->cd(3);
    TGraph *g2_g2x_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g2x_y2_mu_H4[0]) );
    g2_g2x_muH4->SetMarkerColor(kGreen);
    g2_g2x_muH4->SetTitle("g2x");
    g2_g2x_muH4->SetMarkerStyle(21);
    g2_g2x_muH4->SetMarkerSize(0.8);
    g2_g2x_muH4->GetXaxis()->SetTitleSize(0.05);
	g2_g2x_muH4->GetYaxis()->SetTitleSize(0.05);
	g2_g2x_muH4->GetXaxis()->SetLabelSize(0.05);
	g2_g2x_muH4->GetYaxis()->SetLabelSize(0.05);
    g2_g2x_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g2_g2x_muH4->GetYaxis()->SetTitle("Entries [%]");
    g2_g2x_muH4->Draw("SAMEP");

    c3->cd(3);
    TGraph *g3_g2x_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g2x_y3_mu_H4[0]) );
    g3_g2x_muH4->SetMarkerColor(kBlue);
    g3_g2x_muH4->SetTitle("g2x");
    g3_g2x_muH4->SetMarkerStyle(21);
    g3_g2x_muH4->SetMarkerSize(0.8);
    g3_g2x_muH4->GetXaxis()->SetTitleSize(0.05);
	g3_g2x_muH4->GetYaxis()->SetTitleSize(0.05);
	g3_g2x_muH4->GetXaxis()->SetLabelSize(0.05);
	g3_g2x_muH4->GetYaxis()->SetLabelSize(0.05);
    g3_g2x_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g3_g2x_muH4->GetYaxis()->SetTitle("Entries [%]");
    g3_g2x_muH4->Draw("SAMEP");

    c3->cd(3);
    TGraph *g4_g2x_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g2x_y4_mu_H4[0]) );
    g4_g2x_muH4->SetMarkerColor(kMagenta);
    g4_g2x_muH4->SetTitle("g2x");
    g4_g2x_muH4->SetMarkerStyle(21);
    g4_g2x_muH4->SetMarkerSize(0.8);
    g4_g2x_muH4->GetXaxis()->SetTitleSize(0.05);
	g4_g2x_muH4->GetYaxis()->SetTitleSize(0.05);
	g4_g2x_muH4->GetXaxis()->SetLabelSize(0.05);
	g4_g2x_muH4->GetYaxis()->SetLabelSize(0.05);
    g4_g2x_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g4_g2x_muH4->GetYaxis()->SetTitle("Entries [%]");
    g4_g2x_muH4->Draw("SAMEP");

    c3->cd(3);
    TGraph *g5_g2x_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g2x_y5_mu_H4[0]) );
    g5_g2x_muH4->SetMarkerColor(kCyan);
    g5_g2x_muH4->SetTitle("g2x");
    g5_g2x_muH4->SetMarkerStyle(21);
    g5_g2x_muH4->SetMarkerSize(0.8);
    g5_g2x_muH4->GetXaxis()->SetTitleSize(0.05);
	g5_g2x_muH4->GetYaxis()->SetTitleSize(0.05);
	g5_g2x_muH4->GetXaxis()->SetLabelSize(0.05);
	g5_g2x_muH4->GetYaxis()->SetLabelSize(0.05);
    g5_g2x_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g5_g2x_muH4->GetYaxis()->SetTitle("Entries [%]");
    g5_g2x_muH4->Draw("SAMEP");    
    //==========================end: TGraphs for g2x at H4=============================================================================

    //==========================TGraphs for g2y at H4==================================================================================
    c3->cd(4);

	c3->cd(4)->SetGridy(10);

    TGraph *g0_g2y_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g2y_y0_mu_H4[0]) );
    g0_g2y_muH4->SetMarkerColor(kBlack);
    g0_g2y_muH4->SetTitle("g2y");
    g0_g2y_muH4->SetMarkerStyle(21);
    g0_g2y_muH4->SetMarkerSize(0.8);
    g0_g2y_muH4->GetXaxis()->SetTitleSize(0.05);
	g0_g2y_muH4->GetYaxis()->SetTitleSize(0.05);
	g0_g2y_muH4->GetXaxis()->SetLabelSize(0.05);
	g0_g2y_muH4->GetYaxis()->SetLabelSize(0.05);
    g0_g2y_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g0_g2y_muH4->GetYaxis()->SetTitle("Entries [%]");
    g0_g2y_muH4->GetXaxis()->SetLimits(4190,4390);
    g0_g2y_muH4->GetXaxis()->SetNdivisions(506);
    g0_g2y_muH4->GetYaxis()->SetRangeUser(0,100);
    g0_g2y_muH4->Draw("AP");

    c3->cd(4);
    TGraph *g1_g2y_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g2y_y1_mu_H4[0]) );
    g1_g2y_muH4->SetMarkerColor(kRed);
    g1_g2y_muH4->SetTitle("g2y");
    g1_g2y_muH4->SetMarkerStyle(21);
    g1_g2y_muH4->SetMarkerSize(0.8);
    g1_g2y_muH4->GetXaxis()->SetTitleSize(0.05);
	g1_g2y_muH4->GetYaxis()->SetTitleSize(0.05);
	g1_g2y_muH4->GetXaxis()->SetLabelSize(0.05);
	g1_g2y_muH4->GetYaxis()->SetLabelSize(0.05);
    g1_g2y_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g1_g2y_muH4->GetYaxis()->SetTitle("Entries [%]");
    g1_g2y_muH4->Draw("SAMEP");

	c3->cd(4);
    TGraph *g2_g2y_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g2y_y2_mu_H4[0]) );
    g2_g2y_muH4->SetMarkerColor(kGreen);
    g2_g2y_muH4->SetTitle("g2y");
    g2_g2y_muH4->SetMarkerStyle(21);
    g2_g2y_muH4->SetMarkerSize(0.8);
    g2_g2y_muH4->GetXaxis()->SetTitleSize(0.05);
	g2_g2y_muH4->GetYaxis()->SetTitleSize(0.05);
	g2_g2y_muH4->GetXaxis()->SetLabelSize(0.05);
	g2_g2y_muH4->GetYaxis()->SetLabelSize(0.05);
    g2_g2y_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g2_g2y_muH4->GetYaxis()->SetTitle("Entries [%]");
    g2_g2y_muH4->Draw("SAMEP");

    c3->cd(4);
    TGraph *g3_g2y_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g2y_y3_mu_H4[0]) );
    g3_g2y_muH4->SetMarkerColor(kBlue);
    g3_g2y_muH4->SetTitle("g2y");
    g3_g2y_muH4->SetMarkerStyle(21);
    g3_g2y_muH4->SetMarkerSize(0.8);
    g3_g2y_muH4->GetXaxis()->SetTitleSize(0.05);
	g3_g2y_muH4->GetYaxis()->SetTitleSize(0.05);
	g3_g2y_muH4->GetXaxis()->SetLabelSize(0.05);
	g3_g2y_muH4->GetYaxis()->SetLabelSize(0.05);
    g3_g2y_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g3_g2y_muH4->GetYaxis()->SetTitle("Entries [%]");
    g3_g2y_muH4->Draw("SAMEP");

    c3->cd(4);
    TGraph *g4_g2y_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g2y_y4_mu_H4[0]) );
    g4_g2y_muH4->SetMarkerColor(kMagenta);
    g4_g2y_muH4->SetTitle("g2y");
    g4_g2y_muH4->SetMarkerStyle(21);
    g4_g2y_muH4->SetMarkerSize(0.8);
    g4_g2y_muH4->GetXaxis()->SetTitleSize(0.05);
	g4_g2y_muH4->GetYaxis()->SetTitleSize(0.05);
	g4_g2y_muH4->GetXaxis()->SetLabelSize(0.05);
	g4_g2y_muH4->GetYaxis()->SetLabelSize(0.05);
    g4_g2y_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g4_g2y_muH4->GetYaxis()->SetTitle("Entries [%]");
    g4_g2y_muH4->Draw("SAMEP");

    c3->cd(4);
    TGraph *g5_g2y_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g2y_y5_mu_H4[0]) );
    g5_g2y_muH4->SetMarkerColor(kCyan);
    g5_g2y_muH4->SetTitle("g2y");
    g5_g2y_muH4->SetMarkerStyle(21);
    g5_g2y_muH4->SetMarkerSize(0.8);
    g5_g2y_muH4->GetXaxis()->SetTitleSize(0.05);
	g5_g2y_muH4->GetYaxis()->SetTitleSize(0.05);
	g5_g2y_muH4->GetXaxis()->SetLabelSize(0.05);
	g5_g2y_muH4->GetYaxis()->SetLabelSize(0.05);
    g5_g2y_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g5_g2y_muH4->GetYaxis()->SetTitle("Entries [%]");
    g5_g2y_muH4->Draw("SAMEP");    
    //==========================end: TGraphs for g2y at H4=============================================================================

    //==========================TGraphs for g3x at H4==================================================================================
    c3->cd(5);

	c3->cd(5)->SetGridy(10);

    TGraph *g0_g3x_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g3x_y0_mu_H4[0]) );
    g0_g3x_muH4->SetMarkerColor(kBlack);
    g0_g3x_muH4->SetTitle("g3x");
    g0_g3x_muH4->SetMarkerStyle(21);
    g0_g3x_muH4->SetMarkerSize(0.8);
    g0_g3x_muH4->GetXaxis()->SetTitleSize(0.05);
	g0_g3x_muH4->GetYaxis()->SetTitleSize(0.05);
	g0_g3x_muH4->GetXaxis()->SetLabelSize(0.05);
	g0_g3x_muH4->GetYaxis()->SetLabelSize(0.05);
    g0_g3x_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g0_g3x_muH4->GetYaxis()->SetTitle("Entries [%]");
    g0_g3x_muH4->GetXaxis()->SetLimits(4190,4390);
    g0_g3x_muH4->GetXaxis()->SetNdivisions(506);
    g0_g3x_muH4->GetYaxis()->SetRangeUser(0,100);
    g0_g3x_muH4->Draw("AP");

    c3->cd(5);
    TGraph *g1_g3x_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g3x_y1_mu_H4[0]) );
    g1_g3x_muH4->SetMarkerColor(kRed);
    g1_g3x_muH4->SetTitle("g3x");
    g1_g3x_muH4->SetMarkerStyle(21);
    g1_g3x_muH4->SetMarkerSize(0.8);
    g1_g3x_muH4->GetXaxis()->SetTitleSize(0.05);
	g1_g3x_muH4->GetYaxis()->SetTitleSize(0.05);
	g1_g3x_muH4->GetXaxis()->SetLabelSize(0.05);
	g1_g3x_muH4->GetYaxis()->SetLabelSize(0.05);
    g1_g3x_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g1_g3x_muH4->GetYaxis()->SetTitle("Entries [%]");
    g1_g3x_muH4->Draw("SAMEP");

	c3->cd(5);
    TGraph *g2_g3x_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g3x_y2_mu_H4[0]) );
    g2_g3x_muH4->SetMarkerColor(kGreen);
    g2_g3x_muH4->SetTitle("g3x");
    g2_g3x_muH4->SetMarkerStyle(21);
    g2_g3x_muH4->SetMarkerSize(0.8);
    g2_g3x_muH4->GetXaxis()->SetTitleSize(0.05);
	g2_g3x_muH4->GetYaxis()->SetTitleSize(0.05);
	g2_g3x_muH4->GetXaxis()->SetLabelSize(0.05);
	g2_g3x_muH4->GetYaxis()->SetLabelSize(0.05);
    g2_g3x_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g2_g3x_muH4->GetYaxis()->SetTitle("Entries [%]");
    g2_g3x_muH4->Draw("SAMEP");

    c3->cd(5);
    TGraph *g3_g3x_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g3x_y3_mu_H4[0]) );
    g3_g3x_muH4->SetMarkerColor(kBlue);
    g3_g3x_muH4->SetTitle("g3x");
    g3_g3x_muH4->SetMarkerStyle(21);
    g3_g3x_muH4->SetMarkerSize(0.8);
    g3_g3x_muH4->GetXaxis()->SetTitleSize(0.05);
	g3_g3x_muH4->GetYaxis()->SetTitleSize(0.05);
	g3_g3x_muH4->GetXaxis()->SetLabelSize(0.05);
	g3_g3x_muH4->GetYaxis()->SetLabelSize(0.05);
    g3_g3x_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g3_g3x_muH4->GetYaxis()->SetTitle("Entries [%]");
    g3_g3x_muH4->Draw("SAMEP");

    c3->cd(5);
    TGraph *g4_g3x_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g3x_y4_mu_H4[0]) );
    g4_g3x_muH4->SetMarkerColor(kMagenta);
    g4_g3x_muH4->SetTitle("g3x");
    g4_g3x_muH4->SetMarkerStyle(21);
    g4_g3x_muH4->SetMarkerSize(0.8);
    g4_g3x_muH4->GetXaxis()->SetTitleSize(0.05);
	g4_g3x_muH4->GetYaxis()->SetTitleSize(0.05);
	g4_g3x_muH4->GetXaxis()->SetLabelSize(0.05);
	g4_g3x_muH4->GetYaxis()->SetLabelSize(0.05);
    g4_g3x_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g4_g3x_muH4->GetYaxis()->SetTitle("Entries [%]");
    g4_g3x_muH4->Draw("SAMEP");

    c3->cd(5);
    TGraph *g5_g3x_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g3x_y5_mu_H4[0]) );
    g5_g3x_muH4->SetMarkerColor(kCyan);
    g5_g3x_muH4->SetTitle("g3x");
    g5_g3x_muH4->SetMarkerStyle(21);
    g5_g3x_muH4->SetMarkerSize(0.8);
    g5_g3x_muH4->GetXaxis()->SetTitleSize(0.05);
	g5_g3x_muH4->GetYaxis()->SetTitleSize(0.05);
	g5_g3x_muH4->GetXaxis()->SetLabelSize(0.05);
	g5_g3x_muH4->GetYaxis()->SetLabelSize(0.05);
    g5_g3x_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g5_g3x_muH4->GetYaxis()->SetTitle("Entries [%]");
    g5_g3x_muH4->Draw("SAMEP");    
    //==========================end: TGraphs for g3x at H4=============================================================================


    //==========================TGraphs for g3y at H4==================================================================================
    c3->cd(6);

	c3->cd(6)->SetGridy(10);

    TGraph *g0_g3y_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g3y_y0_mu_H4[0]) );
    g0_g3y_muH4->SetMarkerColor(kBlack);
    g0_g3y_muH4->SetTitle("g3y");
    g0_g3y_muH4->SetMarkerStyle(21);
    g0_g3y_muH4->SetMarkerSize(0.8);
    g0_g3y_muH4->GetXaxis()->SetTitleSize(0.05);
	g0_g3y_muH4->GetYaxis()->SetTitleSize(0.05);
	g0_g3y_muH4->GetXaxis()->SetLabelSize(0.05);
	g0_g3y_muH4->GetYaxis()->SetLabelSize(0.05);
    g0_g3y_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g0_g3y_muH4->GetYaxis()->SetTitle("Entries [%]");
    g0_g3y_muH4->GetXaxis()->SetLimits(4190,4390);
    g0_g3y_muH4->GetXaxis()->SetNdivisions(506);
    g0_g3y_muH4->GetYaxis()->SetRangeUser(0,100);
    g0_g3y_muH4->Draw("AP");

    c3->cd(6);
    TGraph *g1_g3y_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g3y_y1_mu_H4[0]) );
    g1_g3y_muH4->SetMarkerColor(kRed);
    g1_g3y_muH4->SetTitle("g3y");
    g1_g3y_muH4->SetMarkerStyle(21);
    g1_g3y_muH4->SetMarkerSize(0.8);
    g1_g3y_muH4->GetXaxis()->SetTitleSize(0.05);
	g1_g3y_muH4->GetYaxis()->SetTitleSize(0.05);
	g1_g3y_muH4->GetXaxis()->SetLabelSize(0.05);
	g1_g3y_muH4->GetYaxis()->SetLabelSize(0.05);
    g1_g3y_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g1_g3y_muH4->GetYaxis()->SetTitle("Entries [%]");
    g1_g3y_muH4->Draw("SAMEP");

	c3->cd(6);
    TGraph *g2_g3y_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g3y_y2_mu_H4[0]) );
    g2_g3y_muH4->SetMarkerColor(kGreen);
    g2_g3y_muH4->SetTitle("g3y");
    g2_g3y_muH4->SetMarkerStyle(21);
    g2_g3y_muH4->SetMarkerSize(0.8);
    g2_g3y_muH4->GetXaxis()->SetTitleSize(0.05);
	g2_g3y_muH4->GetYaxis()->SetTitleSize(0.05);
	g2_g3y_muH4->GetXaxis()->SetLabelSize(0.05);
	g2_g3y_muH4->GetYaxis()->SetLabelSize(0.05);
    g2_g3y_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g2_g3y_muH4->GetYaxis()->SetTitle("Entries [%]");
    g2_g3y_muH4->Draw("SAMEP");

    c3->cd(6);
    TGraph *g3_g3y_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g3y_y3_mu_H4[0]) );
    g3_g3y_muH4->SetMarkerColor(kBlue);
    g3_g3y_muH4->SetTitle("g3y");
    g3_g3y_muH4->SetMarkerStyle(21);
    g3_g3y_muH4->SetMarkerSize(0.8);
    g3_g3y_muH4->GetXaxis()->SetTitleSize(0.05);
	g3_g3y_muH4->GetYaxis()->SetTitleSize(0.05);
	g3_g3y_muH4->GetXaxis()->SetLabelSize(0.05);
	g3_g3y_muH4->GetYaxis()->SetLabelSize(0.05);
    g3_g3y_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g3_g3y_muH4->GetYaxis()->SetTitle("Entries [%]");
    g3_g3y_muH4->Draw("SAMEP");

    c3->cd(6);
    TGraph *g4_g3y_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g3y_y4_mu_H4[0]) );
    g4_g3y_muH4->SetMarkerColor(kMagenta);
    g4_g3y_muH4->SetTitle("g3y");
    g4_g3y_muH4->SetMarkerStyle(21);
    g4_g3y_muH4->SetMarkerSize(0.8);
    g4_g3y_muH4->GetXaxis()->SetTitleSize(0.05);
	g4_g3y_muH4->GetYaxis()->SetTitleSize(0.05);
	g4_g3y_muH4->GetXaxis()->SetLabelSize(0.05);
	g4_g3y_muH4->GetYaxis()->SetLabelSize(0.05);
    g4_g3y_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g4_g3y_muH4->GetYaxis()->SetTitle("Entries [%]");
    g4_g3y_muH4->Draw("SAMEP");

    c3->cd(6);
    TGraph *g5_g3y_muH4 = new TGraph ( x_mu_H4.size() , &(x_mu_H4[0]) , &(g3y_y5_mu_H4[0]) );
    g5_g3y_muH4->SetMarkerColor(kCyan);
    g5_g3y_muH4->SetTitle("g3y");
    g5_g3y_muH4->SetMarkerStyle(21);
    g5_g3y_muH4->SetMarkerSize(0.8);
    g5_g3y_muH4->GetXaxis()->SetTitleSize(0.05);
	g5_g3y_muH4->GetYaxis()->SetTitleSize(0.05);
	g5_g3y_muH4->GetXaxis()->SetLabelSize(0.05);
	g5_g3y_muH4->GetYaxis()->SetLabelSize(0.05);
    g5_g3y_muH4->GetXaxis()->SetTitle("Voltage [V]");
    g5_g3y_muH4->GetYaxis()->SetTitle("Entries [%]");
    g5_g3y_muH4->Draw("SAMEP");    
    //==========================end: TGraphs for g3y at H4=============================================================================

    canv3->cd();
    TPad *newpad3 = new TPad("newpad3","a transparent pad",0,0,1,1);
	newpad3->SetFillStyle(4000);
	newpad3->Draw();
	newpad3->cd();
	TPaveLabel *title3 = new TPaveLabel (0.01,0.94,0.4,0.98,H4mutitle);
	title3->SetFillColor(kWhite);
	title3->Draw();
    TLegend *leg3 = new TLegend(0.515, 0.92, 0.96, 0.995);
	leg3->SetFillColor(0);
	leg3-> SetNColumns(2);
	//leg->SetTextFont(62);
	leg3->SetTextSize(0.02);
	//leg->SetHeader("");
	leg3->AddEntry(g0_g1x_muH4, "Fraction of events with 0 Clusters", "p");
	leg3->AddEntry(g1_g1x_muH4, "Fraction of events with 1 Clusters", "p");
	leg3->AddEntry(g2_g1x_muH4, "Fraction of events with 2 Clusters", "p");
	leg3->AddEntry(g3_g1x_muH4, "Fraction of events with 3 Clusters", "p");
	leg3->AddEntry(g4_g1x_muH4, "Fraction of events with 4 Clusters", "p");
	leg3->AddEntry(g5_g1x_muH4, "Fraction of events with 5 Clusters", "p");
	leg3->Draw();
//===========================================END: draw canvas for MUON runs at H4======================================================================================



//===========================================START: draw canvas for PION runs at H4======================================================================================
    //==========================TGraphs for g1x at H4==================================================================================
    c4->cd(1);

	c4->cd(1)->SetGridy(10);

    TGraph *g0_g1x_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g1x_y0_pi_H4[0]) );
    g0_g1x_piH4->SetMarkerColor(kBlack);
    g0_g1x_piH4->SetTitle("g1x");
    g0_g1x_piH4->SetMarkerStyle(21);
    g0_g1x_piH4->SetMarkerSize(0.8);
    g0_g1x_piH4->GetXaxis()->SetTitleSize(0.05);
	g0_g1x_piH4->GetYaxis()->SetTitleSize(0.05);
	g0_g1x_piH4->GetXaxis()->SetLabelSize(0.05);
	g0_g1x_piH4->GetYaxis()->SetLabelSize(0.05);
    g0_g1x_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g0_g1x_piH4->GetYaxis()->SetTitle("Entries [%]");
    g0_g1x_piH4->GetXaxis()->SetLimits(4190,4390);
    g0_g1x_piH4->GetXaxis()->SetNdivisions(506);
    g0_g1x_piH4->GetYaxis()->SetRangeUser(0,100);
    g0_g1x_piH4->Draw("AP");

    c4->cd(1);
    TGraph *g1_g1x_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g1x_y1_pi_H4[0]) );
    g1_g1x_piH4->SetMarkerColor(kRed);
    g1_g1x_piH4->SetTitle("g1x");
    g1_g1x_piH4->SetMarkerStyle(21);
    g1_g1x_piH4->SetMarkerSize(0.8);
    g1_g1x_piH4->GetXaxis()->SetTitleSize(0.05);
	g1_g1x_piH4->GetYaxis()->SetTitleSize(0.05);
	g1_g1x_piH4->GetXaxis()->SetLabelSize(0.05);
	g1_g1x_piH4->GetYaxis()->SetLabelSize(0.05);
    g1_g1x_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g1_g1x_piH4->GetYaxis()->SetTitle("Entries [%]");
    g1_g1x_piH4->Draw("SAMEP");

	c4->cd(1);
    TGraph *g2_g1x_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g1x_y2_pi_H4[0]) );
    g2_g1x_piH4->SetMarkerColor(kGreen);
    g2_g1x_piH4->SetTitle("g1x");
    g2_g1x_piH4->SetMarkerStyle(21);
    g2_g1x_piH4->SetMarkerSize(0.8);
    g2_g1x_piH4->GetXaxis()->SetTitleSize(0.05);
	g2_g1x_piH4->GetYaxis()->SetTitleSize(0.05);
	g2_g1x_piH4->GetXaxis()->SetLabelSize(0.05);
	g2_g1x_piH4->GetYaxis()->SetLabelSize(0.05);
    g2_g1x_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g2_g1x_piH4->GetYaxis()->SetTitle("Entries [%]");
    g2_g1x_piH4->Draw("SAMEP");

    c4->cd(1);
    TGraph *g3_g1x_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g1x_y3_pi_H4[0]) );
    g3_g1x_piH4->SetMarkerColor(kBlue);
    g3_g1x_piH4->SetTitle("g1x");
    g3_g1x_piH4->SetMarkerStyle(21);
    g3_g1x_piH4->SetMarkerSize(0.8);
    g3_g1x_piH4->GetXaxis()->SetTitleSize(0.05);
	g3_g1x_piH4->GetYaxis()->SetTitleSize(0.05);
	g3_g1x_piH4->GetXaxis()->SetLabelSize(0.05);
	g3_g1x_piH4->GetYaxis()->SetLabelSize(0.05);
    g3_g1x_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g3_g1x_piH4->GetYaxis()->SetTitle("Entries [%]");
    g3_g1x_piH4->Draw("SAMEP");

    c4->cd(1);
    TGraph *g4_g1x_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g1x_y4_pi_H4[0]) );
    g4_g1x_piH4->SetMarkerColor(kMagenta);
    g4_g1x_piH4->SetTitle("g1x");
    g4_g1x_piH4->SetMarkerStyle(21);
    g4_g1x_piH4->SetMarkerSize(0.8);
    g4_g1x_piH4->GetXaxis()->SetTitleSize(0.05);
	g4_g1x_piH4->GetYaxis()->SetTitleSize(0.05);
	g4_g1x_piH4->GetXaxis()->SetLabelSize(0.05);
	g4_g1x_piH4->GetYaxis()->SetLabelSize(0.05);
    g4_g1x_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g4_g1x_piH4->GetYaxis()->SetTitle("Entries [%]");
    g4_g1x_piH4->Draw("SAMEP");

    c4->cd(1);
    TGraph *g5_g1x_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g1x_y5_pi_H4[0]) );
    g5_g1x_piH4->SetMarkerColor(kCyan);
    g5_g1x_piH4->SetTitle("g1x");
    g5_g1x_piH4->SetMarkerStyle(21);
    g5_g1x_piH4->SetMarkerSize(0.8);
    g5_g1x_piH4->GetXaxis()->SetTitleSize(0.05);
	g5_g1x_piH4->GetYaxis()->SetTitleSize(0.05);
	g5_g1x_piH4->GetXaxis()->SetLabelSize(0.05);
	g5_g1x_piH4->GetYaxis()->SetLabelSize(0.05);
    g5_g1x_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g5_g1x_piH4->GetYaxis()->SetTitle("Entries [%]");
    g5_g1x_piH4->Draw("SAMEP");    
    //==========================end: TGraphs for g1x at H4=============================================================================


    //==========================TGraphs for g1y at H4==================================================================================
    c4->cd(2);

	c4->cd(2)->SetGridy(10);

    TGraph *g0_g1y_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g1y_y0_pi_H4[0]) );
    g0_g1y_piH4->SetMarkerColor(kBlack);
    g0_g1y_piH4->SetTitle("g1y");
    g0_g1y_piH4->SetMarkerStyle(21);
    g0_g1y_piH4->SetMarkerSize(0.8);
    g0_g1y_piH4->GetXaxis()->SetTitleSize(0.05);
	g0_g1y_piH4->GetYaxis()->SetTitleSize(0.05);
	g0_g1y_piH4->GetXaxis()->SetLabelSize(0.05);
	g0_g1y_piH4->GetYaxis()->SetLabelSize(0.05);
    g0_g1y_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g0_g1y_piH4->GetYaxis()->SetTitle("Entries [%]");
    g0_g1y_piH4->GetXaxis()->SetLimits(4190,4390);
    g0_g1y_piH4->GetXaxis()->SetNdivisions(506);
    g0_g1y_piH4->GetYaxis()->SetRangeUser(0,100);
    g0_g1y_piH4->Draw("AP");

    c4->cd(2);
    TGraph *g1_g1y_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g1y_y1_pi_H4[0]) );
    g1_g1y_piH4->SetMarkerColor(kRed);
    g1_g1y_piH4->SetTitle("g1y");
    g1_g1y_piH4->SetMarkerStyle(21);
    g1_g1y_piH4->SetMarkerSize(0.8);
    g1_g1y_piH4->GetXaxis()->SetTitleSize(0.05);
	g1_g1y_piH4->GetYaxis()->SetTitleSize(0.05);
	g1_g1y_piH4->GetXaxis()->SetLabelSize(0.05);
	g1_g1y_piH4->GetYaxis()->SetLabelSize(0.05);
    g1_g1y_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g1_g1y_piH4->GetYaxis()->SetTitle("Entries [%]");
    g1_g1y_piH4->Draw("SAMEP");

	c4->cd(2);
    TGraph *g2_g1y_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g1y_y2_pi_H4[0]) );
    g2_g1y_piH4->SetMarkerColor(kGreen);
    g2_g1y_piH4->SetTitle("g1y");
    g2_g1y_piH4->SetMarkerStyle(21);
    g2_g1y_piH4->SetMarkerSize(0.8);
    g2_g1y_piH4->GetXaxis()->SetTitleSize(0.05);
	g2_g1y_piH4->GetYaxis()->SetTitleSize(0.05);
	g2_g1y_piH4->GetXaxis()->SetLabelSize(0.05);
	g2_g1y_piH4->GetYaxis()->SetLabelSize(0.05);
    g2_g1y_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g2_g1y_piH4->GetYaxis()->SetTitle("Entries [%]");
    g2_g1y_piH4->Draw("SAMEP");

    c4->cd(2);
    TGraph *g3_g1y_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g1y_y3_pi_H4[0]) );
    g3_g1y_piH4->SetMarkerColor(kBlue);
    g3_g1y_piH4->SetTitle("g1y");
    g3_g1y_piH4->SetMarkerStyle(21);
    g3_g1y_piH4->SetMarkerSize(0.8);
    g3_g1y_piH4->GetXaxis()->SetTitleSize(0.05);
	g3_g1y_piH4->GetYaxis()->SetTitleSize(0.05);
	g3_g1y_piH4->GetXaxis()->SetLabelSize(0.05);
	g3_g1y_piH4->GetYaxis()->SetLabelSize(0.05);
    g3_g1y_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g3_g1y_piH4->GetYaxis()->SetTitle("Entries [%]");
    g3_g1y_piH4->Draw("SAMEP");

    c4->cd(2);
    TGraph *g4_g1y_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g1y_y4_pi_H4[0]) );
    g4_g1y_piH4->SetMarkerColor(kMagenta);
    g4_g1y_piH4->SetTitle("g1y");
    g4_g1y_piH4->SetMarkerStyle(21);
    g4_g1y_piH4->SetMarkerSize(0.8);
    g4_g1y_piH4->GetXaxis()->SetTitleSize(0.05);
	g4_g1y_piH4->GetYaxis()->SetTitleSize(0.05);
	g4_g1y_piH4->GetXaxis()->SetLabelSize(0.05);
	g4_g1y_piH4->GetYaxis()->SetLabelSize(0.05);
    g4_g1y_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g4_g1y_piH4->GetYaxis()->SetTitle("Entries [%]");
    g4_g1y_piH4->Draw("SAMEP");

    c4->cd(2);
    TGraph *g5_g1y_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g1y_y5_pi_H4[0]) );
    g5_g1y_piH4->SetMarkerColor(kCyan);
    g5_g1y_piH4->SetTitle("g1y");
    g5_g1y_piH4->SetMarkerStyle(21);
    g5_g1y_piH4->SetMarkerSize(0.8);
    g5_g1y_piH4->GetXaxis()->SetTitleSize(0.05);
	g5_g1y_piH4->GetYaxis()->SetTitleSize(0.05);
	g5_g1y_piH4->GetXaxis()->SetLabelSize(0.05);
	g5_g1y_piH4->GetYaxis()->SetLabelSize(0.05);
    g5_g1y_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g5_g1y_piH4->GetYaxis()->SetTitle("Entries [%]");
    g5_g1y_piH4->Draw("SAMEP");    
    //==========================end: TGraphs for g1y at H4=============================================================================


    //==========================TGraphs for g2x at H4==================================================================================
    c4->cd(3);

	c4->cd(3)->SetGridy(10);

    TGraph *g0_g2x_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g2x_y0_pi_H4[0]) );
    g0_g2x_piH4->SetMarkerColor(kBlack);
    g0_g2x_piH4->SetTitle("g2x");
    g0_g2x_piH4->SetMarkerStyle(21);
    g0_g2x_piH4->SetMarkerSize(0.8);
    g0_g2x_piH4->GetXaxis()->SetTitleSize(0.05);
	g0_g2x_piH4->GetYaxis()->SetTitleSize(0.05);
	g0_g2x_piH4->GetXaxis()->SetLabelSize(0.05);
	g0_g2x_piH4->GetYaxis()->SetLabelSize(0.05);
    g0_g2x_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g0_g2x_piH4->GetYaxis()->SetTitle("Entries [%]");
    g0_g2x_piH4->GetXaxis()->SetLimits(4190,4390);
    g0_g2x_piH4->GetXaxis()->SetNdivisions(506);
    g0_g2x_piH4->GetYaxis()->SetRangeUser(0,100);
    g0_g2x_piH4->Draw("AP");

    c4->cd(3);
    TGraph *g1_g2x_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g2x_y1_pi_H4[0]) );
    g1_g2x_piH4->SetMarkerColor(kRed);
    g1_g2x_piH4->SetTitle("g2x");
    g1_g2x_piH4->SetMarkerStyle(21);
    g1_g2x_piH4->SetMarkerSize(0.8);
    g1_g2x_piH4->GetXaxis()->SetTitleSize(0.05);
	g1_g2x_piH4->GetYaxis()->SetTitleSize(0.05);
	g1_g2x_piH4->GetXaxis()->SetLabelSize(0.05);
	g1_g2x_piH4->GetYaxis()->SetLabelSize(0.05);
    g1_g2x_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g1_g2x_piH4->GetYaxis()->SetTitle("Entries [%]");
    g1_g2x_piH4->Draw("SAMEP");

	c4->cd(3);
    TGraph *g2_g2x_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g2x_y2_pi_H4[0]) );
    g2_g2x_piH4->SetMarkerColor(kGreen);
    g2_g2x_piH4->SetTitle("g2x");
    g2_g2x_piH4->SetMarkerStyle(21);
    g2_g2x_piH4->SetMarkerSize(0.8);
    g2_g2x_piH4->GetXaxis()->SetTitleSize(0.05);
	g2_g2x_piH4->GetYaxis()->SetTitleSize(0.05);
	g2_g2x_piH4->GetXaxis()->SetLabelSize(0.05);
	g2_g2x_piH4->GetYaxis()->SetLabelSize(0.05);
    g2_g2x_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g2_g2x_piH4->GetYaxis()->SetTitle("Entries [%]");
    g2_g2x_piH4->Draw("SAMEP");

    c4->cd(3);
    TGraph *g3_g2x_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g2x_y3_pi_H4[0]) );
    g3_g2x_piH4->SetMarkerColor(kBlue);
    g3_g2x_piH4->SetTitle("g2x");
    g3_g2x_piH4->SetMarkerStyle(21);
    g3_g2x_piH4->SetMarkerSize(0.8);
    g3_g2x_piH4->GetXaxis()->SetTitleSize(0.05);
	g3_g2x_piH4->GetYaxis()->SetTitleSize(0.05);
	g3_g2x_piH4->GetXaxis()->SetLabelSize(0.05);
	g3_g2x_piH4->GetYaxis()->SetLabelSize(0.05);
    g3_g2x_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g3_g2x_piH4->GetYaxis()->SetTitle("Entries [%]");
    g3_g2x_piH4->Draw("SAMEP");

    c4->cd(3);
    TGraph *g4_g2x_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g2x_y4_pi_H4[0]) );
    g4_g2x_piH4->SetMarkerColor(kMagenta);
    g4_g2x_piH4->SetTitle("g2x");
    g4_g2x_piH4->SetMarkerStyle(21);
    g4_g2x_piH4->SetMarkerSize(0.8);
    g4_g2x_piH4->GetXaxis()->SetTitleSize(0.05);
	g4_g2x_piH4->GetYaxis()->SetTitleSize(0.05);
	g4_g2x_piH4->GetXaxis()->SetLabelSize(0.05);
	g4_g2x_piH4->GetYaxis()->SetLabelSize(0.05);
    g4_g2x_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g4_g2x_piH4->GetYaxis()->SetTitle("Entries [%]");
    g4_g2x_piH4->Draw("SAMEP");

    c4->cd(3);
    TGraph *g5_g2x_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g2x_y5_pi_H4[0]) );
    g5_g2x_piH4->SetMarkerColor(kCyan);
    g5_g2x_piH4->SetTitle("g2x");
    g5_g2x_piH4->SetMarkerStyle(21);
    g5_g2x_piH4->SetMarkerSize(0.8);
    g5_g2x_piH4->GetXaxis()->SetTitleSize(0.05);
	g5_g2x_piH4->GetYaxis()->SetTitleSize(0.05);
	g5_g2x_piH4->GetXaxis()->SetLabelSize(0.05);
	g5_g2x_piH4->GetYaxis()->SetLabelSize(0.05);
    g5_g2x_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g5_g2x_piH4->GetYaxis()->SetTitle("Entries [%]");
    g5_g2x_piH4->Draw("SAMEP");    
    //==========================end: TGraphs for g2x at H4=============================================================================

    //==========================TGraphs for g2y at H4==================================================================================
    c4->cd(4);

	c4->cd(4)->SetGridy(10);

    TGraph *g0_g2y_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g2y_y0_pi_H4[0]) );
    g0_g2y_piH4->SetMarkerColor(kBlack);
    g0_g2y_piH4->SetTitle("g2y");
    g0_g2y_piH4->SetMarkerStyle(21);
    g0_g2y_piH4->SetMarkerSize(0.8);
    g0_g2y_piH4->GetXaxis()->SetTitleSize(0.05);
	g0_g2y_piH4->GetYaxis()->SetTitleSize(0.05);
	g0_g2y_piH4->GetXaxis()->SetLabelSize(0.05);
	g0_g2y_piH4->GetYaxis()->SetLabelSize(0.05);
    g0_g2y_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g0_g2y_piH4->GetYaxis()->SetTitle("Entries [%]");
    g0_g2y_piH4->GetXaxis()->SetLimits(4190,4390);
    g0_g2y_piH4->GetXaxis()->SetNdivisions(506);
    g0_g2y_piH4->GetYaxis()->SetRangeUser(0,100);
    g0_g2y_piH4->Draw("AP");

    c4->cd(4);
    TGraph *g1_g2y_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g2y_y1_pi_H4[0]) );
    g1_g2y_piH4->SetMarkerColor(kRed);
    g1_g2y_piH4->SetTitle("g2y");
    g1_g2y_piH4->SetMarkerStyle(21);
    g1_g2y_piH4->SetMarkerSize(0.8);
    g1_g2y_piH4->GetXaxis()->SetTitleSize(0.05);
	g1_g2y_piH4->GetYaxis()->SetTitleSize(0.05);
	g1_g2y_piH4->GetXaxis()->SetLabelSize(0.05);
	g1_g2y_piH4->GetYaxis()->SetLabelSize(0.05);
    g1_g2y_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g1_g2y_piH4->GetYaxis()->SetTitle("Entries [%]");
    g1_g2y_piH4->Draw("SAMEP");

	c4->cd(4);
    TGraph *g2_g2y_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g2y_y2_pi_H4[0]) );
    g2_g2y_piH4->SetMarkerColor(kGreen);
    g2_g2y_piH4->SetTitle("g2y");
    g2_g2y_piH4->SetMarkerStyle(21);
    g2_g2y_piH4->SetMarkerSize(0.8);
    g2_g2y_piH4->GetXaxis()->SetTitleSize(0.05);
	g2_g2y_piH4->GetYaxis()->SetTitleSize(0.05);
	g2_g2y_piH4->GetXaxis()->SetLabelSize(0.05);
	g2_g2y_piH4->GetYaxis()->SetLabelSize(0.05);
    g2_g2y_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g2_g2y_piH4->GetYaxis()->SetTitle("Entries [%]");
    g2_g2y_piH4->Draw("SAMEP");

    c4->cd(4);
    TGraph *g3_g2y_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g2y_y3_pi_H4[0]) );
    g3_g2y_piH4->SetMarkerColor(kBlue);
    g3_g2y_piH4->SetTitle("g2y");
    g3_g2y_piH4->SetMarkerStyle(21);
    g3_g2y_piH4->SetMarkerSize(0.8);
    g3_g2y_piH4->GetXaxis()->SetTitleSize(0.05);
	g3_g2y_piH4->GetYaxis()->SetTitleSize(0.05);
	g3_g2y_piH4->GetXaxis()->SetLabelSize(0.05);
	g3_g2y_piH4->GetYaxis()->SetLabelSize(0.05);
    g3_g2y_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g3_g2y_piH4->GetYaxis()->SetTitle("Entries [%]");
    g3_g2y_piH4->Draw("SAMEP");

    c4->cd(4);
    TGraph *g4_g2y_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g2y_y4_pi_H4[0]) );
    g4_g2y_piH4->SetMarkerColor(kMagenta);
    g4_g2y_piH4->SetTitle("g2y");
    g4_g2y_piH4->SetMarkerStyle(21);
    g4_g2y_piH4->SetMarkerSize(0.8);
    g4_g2y_piH4->GetXaxis()->SetTitleSize(0.05);
	g4_g2y_piH4->GetYaxis()->SetTitleSize(0.05);
	g4_g2y_piH4->GetXaxis()->SetLabelSize(0.05);
	g4_g2y_piH4->GetYaxis()->SetLabelSize(0.05);
    g4_g2y_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g4_g2y_piH4->GetYaxis()->SetTitle("Entries [%]");
    g4_g2y_piH4->Draw("SAMEP");

    c4->cd(4);
    TGraph *g5_g2y_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g2y_y5_pi_H4[0]) );
    g5_g2y_piH4->SetMarkerColor(kCyan);
    g5_g2y_piH4->SetTitle("g2y");
    g5_g2y_piH4->SetMarkerStyle(21);
    g5_g2y_piH4->SetMarkerSize(0.8);
    g5_g2y_piH4->GetXaxis()->SetTitleSize(0.05);
	g5_g2y_piH4->GetYaxis()->SetTitleSize(0.05);
	g5_g2y_piH4->GetXaxis()->SetLabelSize(0.05);
	g5_g2y_piH4->GetYaxis()->SetLabelSize(0.05);
    g5_g2y_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g5_g2y_piH4->GetYaxis()->SetTitle("Entries [%]");
    g5_g2y_piH4->Draw("SAMEP");    
    //==========================end: TGraphs for g2y at H4=============================================================================

    //==========================TGraphs for g3x at H4==================================================================================
    c4->cd(5);

	c4->cd(5)->SetGridy(10);

    TGraph *g0_g3x_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g3x_y0_pi_H4[0]) );
    g0_g3x_piH4->SetMarkerColor(kBlack);
    g0_g3x_piH4->SetTitle("g3x");
    g0_g3x_piH4->SetMarkerStyle(21);
    g0_g3x_piH4->SetMarkerSize(0.8);
    g0_g3x_piH4->GetXaxis()->SetTitleSize(0.05);
	g0_g3x_piH4->GetYaxis()->SetTitleSize(0.05);
	g0_g3x_piH4->GetXaxis()->SetLabelSize(0.05);
	g0_g3x_piH4->GetYaxis()->SetLabelSize(0.05);
    g0_g3x_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g0_g3x_piH4->GetYaxis()->SetTitle("Entries [%]");
    g0_g3x_piH4->GetXaxis()->SetLimits(4190,4390);
    g0_g3x_piH4->GetXaxis()->SetNdivisions(506);
    g0_g3x_piH4->GetYaxis()->SetRangeUser(0,100);
    g0_g3x_piH4->Draw("AP");

    c4->cd(5);
    TGraph *g1_g3x_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g3x_y1_pi_H4[0]) );
    g1_g3x_piH4->SetMarkerColor(kRed);
    g1_g3x_piH4->SetTitle("g3x");
    g1_g3x_piH4->SetMarkerStyle(21);
    g1_g3x_piH4->SetMarkerSize(0.8);
    g1_g3x_piH4->GetXaxis()->SetTitleSize(0.05);
	g1_g3x_piH4->GetYaxis()->SetTitleSize(0.05);
	g1_g3x_piH4->GetXaxis()->SetLabelSize(0.05);
	g1_g3x_piH4->GetYaxis()->SetLabelSize(0.05);
    g1_g3x_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g1_g3x_piH4->GetYaxis()->SetTitle("Entries [%]");
    g1_g3x_piH4->Draw("SAMEP");

	c4->cd(5);
    TGraph *g2_g3x_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g3x_y2_pi_H4[0]) );
    g2_g3x_piH4->SetMarkerColor(kGreen);
    g2_g3x_piH4->SetTitle("g3x");
    g2_g3x_piH4->SetMarkerStyle(21);
    g2_g3x_piH4->SetMarkerSize(0.8);
    g2_g3x_piH4->GetXaxis()->SetTitleSize(0.05);
	g2_g3x_piH4->GetYaxis()->SetTitleSize(0.05);
	g2_g3x_piH4->GetXaxis()->SetLabelSize(0.05);
	g2_g3x_piH4->GetYaxis()->SetLabelSize(0.05);
    g2_g3x_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g2_g3x_piH4->GetYaxis()->SetTitle("Entries [%]");
    g2_g3x_piH4->Draw("SAMEP");

    c4->cd(5);
    TGraph *g3_g3x_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g3x_y3_pi_H4[0]) );
    g3_g3x_piH4->SetMarkerColor(kBlue);
    g3_g3x_piH4->SetTitle("g3x");
    g3_g3x_piH4->SetMarkerStyle(21);
    g3_g3x_piH4->SetMarkerSize(0.8);
    g3_g3x_piH4->GetXaxis()->SetTitleSize(0.05);
	g3_g3x_piH4->GetYaxis()->SetTitleSize(0.05);
	g3_g3x_piH4->GetXaxis()->SetLabelSize(0.05);
	g3_g3x_piH4->GetYaxis()->SetLabelSize(0.05);
    g3_g3x_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g3_g3x_piH4->GetYaxis()->SetTitle("Entries [%]");
    g3_g3x_piH4->Draw("SAMEP");

    c4->cd(5);
    TGraph *g4_g3x_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g3x_y4_pi_H4[0]) );
    g4_g3x_piH4->SetMarkerColor(kMagenta);
    g4_g3x_piH4->SetTitle("g3x");
    g4_g3x_piH4->SetMarkerStyle(21);
    g4_g3x_piH4->SetMarkerSize(0.8);
    g4_g3x_piH4->GetXaxis()->SetTitleSize(0.05);
	g4_g3x_piH4->GetYaxis()->SetTitleSize(0.05);
	g4_g3x_piH4->GetXaxis()->SetLabelSize(0.05);
	g4_g3x_piH4->GetYaxis()->SetLabelSize(0.05);
    g4_g3x_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g4_g3x_piH4->GetYaxis()->SetTitle("Entries [%]");
    g4_g3x_piH4->Draw("SAMEP");

    c4->cd(5);
    TGraph *g5_g3x_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g3x_y5_pi_H4[0]) );
    g5_g3x_piH4->SetMarkerColor(kCyan);
    g5_g3x_piH4->SetTitle("g3x");
    g5_g3x_piH4->SetMarkerStyle(21);
    g5_g3x_piH4->SetMarkerSize(0.8);
    g5_g3x_piH4->GetXaxis()->SetTitleSize(0.05);
	g5_g3x_piH4->GetYaxis()->SetTitleSize(0.05);
	g5_g3x_piH4->GetXaxis()->SetLabelSize(0.05);
	g5_g3x_piH4->GetYaxis()->SetLabelSize(0.05);
    g5_g3x_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g5_g3x_piH4->GetYaxis()->SetTitle("Entries [%]");
    g5_g3x_piH4->Draw("SAMEP");    
    //==========================end: TGraphs for g3x at H4=============================================================================


    //==========================TGraphs for g3y at H4==================================================================================
    c4->cd(6);

	c4->cd(6)->SetGridy(10);

    TGraph *g0_g3y_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g3y_y0_pi_H4[0]) );
    g0_g3y_piH4->SetMarkerColor(kBlack);
    g0_g3y_piH4->SetTitle("g3y");
    g0_g3y_piH4->SetMarkerStyle(21);
    g0_g3y_piH4->SetMarkerSize(0.8);
    g0_g3y_piH4->GetXaxis()->SetTitleSize(0.05);
	g0_g3y_piH4->GetYaxis()->SetTitleSize(0.05);
	g0_g3y_piH4->GetXaxis()->SetLabelSize(0.05);
	g0_g3y_piH4->GetYaxis()->SetLabelSize(0.05);
    g0_g3y_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g0_g3y_piH4->GetYaxis()->SetTitle("Entries [%]");
    g0_g3y_piH4->GetXaxis()->SetLimits(4190,4390);
    g0_g3y_piH4->GetXaxis()->SetNdivisions(506);
    g0_g3y_piH4->GetYaxis()->SetRangeUser(0,100);
    g0_g3y_piH4->Draw("AP");

    c4->cd(6);
    TGraph *g1_g3y_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g3y_y1_pi_H4[0]) );
    g1_g3y_piH4->SetMarkerColor(kRed);
    g1_g3y_piH4->SetTitle("g3y");
    g1_g3y_piH4->SetMarkerStyle(21);
    g1_g3y_piH4->SetMarkerSize(0.8);
    g1_g3y_piH4->GetXaxis()->SetTitleSize(0.05);
	g1_g3y_piH4->GetYaxis()->SetTitleSize(0.05);
	g1_g3y_piH4->GetXaxis()->SetLabelSize(0.05);
	g1_g3y_piH4->GetYaxis()->SetLabelSize(0.05);
    g1_g3y_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g1_g3y_piH4->GetYaxis()->SetTitle("Entries [%]");
    g1_g3y_piH4->Draw("SAMEP");

	c4->cd(6);
    TGraph *g2_g3y_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g3y_y2_pi_H4[0]) );
    g2_g3y_piH4->SetMarkerColor(kGreen);
    g2_g3y_piH4->SetTitle("g3y");
    g2_g3y_piH4->SetMarkerStyle(21);
    g2_g3y_piH4->SetMarkerSize(0.8);
    g2_g3y_piH4->GetXaxis()->SetTitleSize(0.05);
	g2_g3y_piH4->GetYaxis()->SetTitleSize(0.05);
	g2_g3y_piH4->GetXaxis()->SetLabelSize(0.05);
	g2_g3y_piH4->GetYaxis()->SetLabelSize(0.05);
    g2_g3y_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g2_g3y_piH4->GetYaxis()->SetTitle("Entries [%]");
    g2_g3y_piH4->Draw("SAMEP");

    c4->cd(6);
    TGraph *g3_g3y_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g3y_y3_pi_H4[0]) );
    g3_g3y_piH4->SetMarkerColor(kBlue);
    g3_g3y_piH4->SetTitle("g3y");
    g3_g3y_piH4->SetMarkerStyle(21);
    g3_g3y_piH4->SetMarkerSize(0.8);
    g3_g3y_piH4->GetXaxis()->SetTitleSize(0.05);
	g3_g3y_piH4->GetYaxis()->SetTitleSize(0.05);
	g3_g3y_piH4->GetXaxis()->SetLabelSize(0.05);
	g3_g3y_piH4->GetYaxis()->SetLabelSize(0.05);
    g3_g3y_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g3_g3y_piH4->GetYaxis()->SetTitle("Entries [%]");
    g3_g3y_piH4->Draw("SAMEP");

    c4->cd(6);
    TGraph *g4_g3y_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g3y_y4_pi_H4[0]) );
    g4_g3y_piH4->SetMarkerColor(kMagenta);
    g4_g3y_piH4->SetTitle("g3y");
    g4_g3y_piH4->SetMarkerStyle(21);
    g4_g3y_piH4->SetMarkerSize(0.8);
    g4_g3y_piH4->GetXaxis()->SetTitleSize(0.05);
	g4_g3y_piH4->GetYaxis()->SetTitleSize(0.05);
	g4_g3y_piH4->GetXaxis()->SetLabelSize(0.05);
	g4_g3y_piH4->GetYaxis()->SetLabelSize(0.05);
    g4_g3y_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g4_g3y_piH4->GetYaxis()->SetTitle("Entries [%]");
    g4_g3y_piH4->Draw("SAMEP");

    c4->cd(6);
    TGraph *g5_g3y_piH4 = new TGraph ( x_pi_H4.size() , &(x_pi_H4[0]) , &(g3y_y5_pi_H4[0]) );
    g5_g3y_piH4->SetMarkerColor(kCyan);
    g5_g3y_piH4->SetTitle("g3y");
    g5_g3y_piH4->SetMarkerStyle(21);
    g5_g3y_piH4->SetMarkerSize(0.8);
    g5_g3y_piH4->GetXaxis()->SetTitleSize(0.05);
	g5_g3y_piH4->GetYaxis()->SetTitleSize(0.05);
	g5_g3y_piH4->GetXaxis()->SetLabelSize(0.05);
	g5_g3y_piH4->GetYaxis()->SetLabelSize(0.05);
    g5_g3y_piH4->GetXaxis()->SetTitle("Voltage [V]");
    g5_g3y_piH4->GetYaxis()->SetTitle("Entries [%]");
    g5_g3y_piH4->Draw("SAMEP");    
    //==========================end: TGraphs for g3y at H4=============================================================================

    canv4->cd();
    TPad *newpad4 = new TPad("newpad4","a transparent pad",0,0,1,1);
	newpad4->SetFillStyle(4000);
	newpad4->Draw();
	newpad4->cd();
	TPaveLabel *title4 = new TPaveLabel (0.01,0.94,0.4,0.98,H4pititle);
	title4->SetFillColor(kWhite);
	title4->Draw();
    TLegend *leg4 = new TLegend(0.515, 0.92, 0.96, 0.995);
	leg4->SetFillColor(0);
	leg4-> SetNColumns(2);
	//leg4->SetTextFont(62);
	leg4->SetTextSize(0.02);
	//leg4->SetHeader("");
	leg4->AddEntry(g0_g1x_piH4, "Fraction of events with 0 Clusters", "p");
	leg4->AddEntry(g1_g1x_piH4, "Fraction of events with 1 Clusters", "p");
	leg4->AddEntry(g2_g1x_piH4, "Fraction of events with 2 Clusters", "p");
	leg4->AddEntry(g3_g1x_piH4, "Fraction of events with 3 Clusters", "p");
	leg4->AddEntry(g4_g1x_piH4, "Fraction of events with 4 Clusters", "p");
	leg4->AddEntry(g5_g1x_piH4, "Fraction of events with 5 Clusters", "p");
	leg4->Draw();
//===========================================END: draw canvas for PION runs at H4======================================================================================



    myapp->Run();
    return 0;
}