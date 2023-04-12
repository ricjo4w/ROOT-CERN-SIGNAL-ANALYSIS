/*
	Author----------------------->John W. Rice
	Last Revision---------------->July/24/2017
	Depndencies------------------>None
*/
#include <iostream>
#include <TLegend.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TH1F.h>
#include <TGraph.h>

using namespace std;

void Grapher(TString rootName, TString inFile, float lim, TString resultLoc){
//void Grapher(){
	
	//const TString rootName = "mu_70_GC_LD2_3_mcR_mess_NsW_kT_kD_NC_SB";
	//const TString inFile = "./Trees2/mu_70_GC_LD2_3_mcR_mess_NsW_kT_kD_NC_SB.root";
	//const float lim  = 1000;
	//const TString resultLoc = "./results/mu_70_GC_LD2_3_mcR_mess_NsW_kT_kD_NC_SB_Batch_20_15/";
	
	const float entCount = lim;
	
//##################################################################################################################	
//                                          *** Set Output Streams ***
//##################################################################################################################
	TString resVar = "nnResponse";//name of branch which contains response from method
	TString typeVar = "dimuon";//name of branch declaring Signal or Background
	bool twoRoots = true; //true == use two root files || false == use one root file
	TDirectory *td = gROOT;
	TDirectory *cdtof = td->CurrentDirectory()->mkdir("tof");
	
	ofstream outSAE(resultLoc + "ofstreams/" + rootName + "_Signal_Acceptance_Eficiency.txt", ofstream::trunc);
	ofstream outBRE(resultLoc + "ofstreams/" + rootName + "_Background_Rejection_Eficiency.txt", ofstream::trunc);
	ofstream outPur(resultLoc + "ofstreams/" + rootName + "_Purity.txt", ofstream::trunc);
	ofstream outOpt(resultLoc + "ofstreams/" + rootName + "_Signal_Optimization.txt", ofstream::trunc);
	ofstream outH1(resultLoc + "ofstreams/" + rootName + "_H1.txt", ofstream::trunc);
	ofstream outH2(resultLoc + "ofstreams/" + rootName + "_H2.txt", ofstream::trunc);
	ofstream outNN(resultLoc + "ofstreams/" + rootName + "_NN_Second.txt", ofstream::trunc);
	
//##################################################################################################################
//                                 *** Make TFile signalTree and Main Canvas ***
//##################################################################################################################
	TCanvas* c1 = new TCanvas("c1", "c1");
	//TFile *target = new TFile(inFile,"READ");
	TFile *target = TFile::Open( inFile );
	cout << "The File is: " << inFile << endl;
	target->cd();
	TTree *t1 = (TTree *) target->Get("signal");
	
	Float_t sep1;
	Float_t sep2;
	int dimuon; 
	//float purity;
	
//##################################################################################################################
//                                            *** Make Histograms ***
//##################################################################################################################
	TH1F *h1= new TH1F("h1",rootName + " Signal response distribution", entCount, 0,1);
	TH1F *h2= new TH1F("h2",rootName + " Backgrund response distribution",entCount, 0,1);
	TH1F *h3= new TH1F("h3",rootName + " Signal Cut distribution", entCount, 0,1);
	TH1F *h4= new TH1F("h4",rootName + " Backgrund Cut distribution", entCount, 0,1);
	TH1F *h5= new TH1F("h5",rootName + " Purity", entCount, 0,1);
		h5->GetXaxis()->SetTitle("Cut");
	TH1F *h6= new TH1F("h6",rootName + " Signal Optimization",entCount,0,1);
		h6->GetXaxis()->SetTitle("Cut");
	
//##################################################################################################################
//                                         *** Fill Histogram 1 and 2 ***
//##################################################################################################################
	if (twoRoots) {
		TTree *t2 = (TTree *) target->Get("background");//background tree
		
		t1->SetBranchAddress(resVar, &sep1);
		t2->SetBranchAddress(resVar, &sep2);
		int loopLim;
		if (t1->GetEntries() > t2->GetEntries()) {
			loopLim = t2->GetEntries();
		} else {
			loopLim = t1->GetEntries();
		}
		for(int i=0; i< loopLim; i++){	
			t2->GetEntry(i);
			t1->GetEntry(i);
			h2->Fill(sep2);
			h1->Fill(sep1);
			outH1 << "Entry " << i << ": " << sep1 << endl;
			outH2 << "Entry " << i << ": " << sep2 << endl;
		}
		
	}

//##################################################################################################################
//                         *** Output Histogram 1 & 2 to 1 Histogram in Canvas ***
//##################################################################################################################
	bool first=false;
	float dtotal = h1->Integral();
	float btotal = h2->Integral();
	
	TPad* p1 = new TPad("p1","",0.0,0.1,1,1.0,0);
	p1->Draw();
	
	TPad* p2 = new TPad("p1","",0,0,1,0.1,0);
	p2->Draw();
	
		TLegend* legend0Left = new TLegend(0,0,0.5,1);
			legend0Left->SetTextColor(kWhite);
			legend0Left->SetFillColor(kBlack);
			legend0Left->AddEntry(h1,"Signal Response Distribution","le");
			legend0Left->SetBorderSize(0);
			
		TLegend* legend0Right = new TLegend(1,0,0.5,1);
			legend0Right->SetTextColor(kWhite);
			legend0Right->SetFillColor(kBlack);
			legend0Right->AddEntry(h2,"Background Response Distribution","le");
			legend0Right->SetBorderSize(0);
	p1->cd();
		h1->SetStats(false);
		h2->SetStats(false);
		h1->Draw();
		h2->Draw("same");
	p2->cd();
		legend0Left->Draw();
		legend0Right->Draw();
	c1->cd();
	
	float sigAccEff[entCount];
	float backRejEff[entCount];
	
	float purity[entCount];
	
	float sigOpt[entCount];
	
	float x = 1/entCount;
	float b = 0.1/entCount;

//##################################################################################################################
//                             *** Calculate and Fill Histogram 3, 4, 5, & 6 ***
//##################################################################################################################
	
	for(int i=0; i<entCount; i++){
		float cut =i*x;//Setting the cut value||float cut =i*0.001
		float sigBins;//Number of points in a range of bins for the signal
		sigBins = (h1->Integral(i, entCount ));//Recieving number of points between bin i and 100
		float backBins;//Number of points in a range of bins for the background
		backBins = (h2->Integral(0, i+1));//Recieving number of points between bin 0 and i
		
		//*** return signal acceptance efficiency and background rejection efficiency ***
		sigAccEff[i] = sigBins/dtotal;
		backRejEff[i] = backBins/dtotal;
		outSAE << "Entry " << i + 1 << " - " << sigAccEff[i] << endl;
		outBRE << "Entry " << i + 1 << " - " << backRejEff[i] << endl;
		
		
		//*** return purtiy ***
		float conVar = 1 - backRejEff[i];
		purity[i] = sigAccEff[i] / (sigAccEff[i] + conVar);
		outPur << "Entry " << i + 1 << " - " << purity[i] << endl;
		
		//*** return signal optimization ***
		sigOpt[i] = sigAccEff[i] * purity[i];
		outOpt << "Entry " << i + 1 << " - " << sigOpt[i] << endl;
		
		//*** graph signal acceptance efficiency and background rejection efficiency ***
		h3->Fill(cut + b, sigBins/dtotal);//signal acceptance efficiency
		h4->Fill(cut + b, backBins/btotal);//background rejection efficiency
		
		//*** graph purity and signal optimization ***
		h5->Fill(cut + b, purity[i]);
		h6->Fill(cut + b, sigOpt[i]);
	}
	
//##################################################################################################################
//                                *** Draw Histogram 3, 4, 5, & 6 to Canvas
//##################################################################################################################
	
	h1->SetLineColor(kBlue);
	h2->SetLineColor(kRed);
	c1->SaveAs(resultLoc + rootName + "_Sig_Back_Response_Distro.png");		
	
	h3->SetLineColor(kBlue);
	h4->SetLineColor(kRed);
	
	TPad* p3 = new TPad("p1","",0.0,0.1,1,1.0,0);
	p3->Draw();
	
	TPad* p4 = new TPad("p1","",0,0,1,0.1,0);
	p4->Draw();
	
		TLegend* legend1Left = new TLegend(0,0,0.5,1);
			legend1Left->SetTextColor(kWhite);
			legend1Left->SetFillColor(kBlack);
			legend1Left->AddEntry(h3,"Signal Cut Distribution","le");
			legend1Left->SetBorderSize(0);
			
		TLegend* legend1Right = new TLegend(1,0,0.5,1);
			legend1Right->SetTextColor(kWhite);
			legend1Right->SetFillColor(kBlack);
			legend1Right->AddEntry(h4,"Background Cut Distribution","le");
			legend1Right->SetBorderSize(0);
	
	p3->cd();
	//h3->SetStats(false);
	//h4->SetStats(false);
	h3->Draw();
	h4->Draw("same");
	
	p4->cd();
	legend1Left->Draw();
	legend1Right->Draw();
	c1->cd();
	c1->SaveAs(resultLoc + rootName + "_Sig_Back_Cut_Distro.png");
	
	h5->SetLineColor(kBlue);
	h6->SetLineColor(kRed);
	
	TPad* p5 = new TPad("p1","",0.0,0.1,1,1.0,0);
	p5->Draw();
	
	TPad* p6 = new TPad("p1","",0,0,1,0.1,0);
	p6->Draw();
	
		TLegend* legend2Left = new TLegend(0,0,0.5,1);
			legend2Left->SetTextColor(kWhite);
			legend2Left->SetFillColor(kBlack);
			legend2Left->AddEntry(h5,"Purity","le");
			legend2Left->SetBorderSize(0);
			
		TLegend* legend2Right = new TLegend(1,0,0.5,1);
			legend2Right->SetTextColor(kWhite);
			legend2Right->SetFillColor(kBlack);
			legend2Right->AddEntry(h6,"Signal Optimization","le");
			legend2Right->SetBorderSize(0);
	
	p5->cd();
	h5->SetStats(false);
	h6->SetStats(false);
	h5->Draw();
	h6->Draw("same");
	
	p6->cd();
	legend2Left->Draw();
	legend2Right->Draw();
	c1->cd();
	c1->SaveAs(resultLoc + rootName + "_Signal_Optimization_and_Purity.png");

	TCanvas *c2 = new TCanvas("c2",rootName + " ROC Curve",200,10,700,500);

	c2->SetGrid();

	const Int_t n = sizeof(sigAccEff);//sets n to the size of the arrays use.
	cout << "Size: " << n << endl;

//##################################################################################################################
//                                     ***Creating ROC Curve with TGraph***
//##################################################################################################################
	TGraph *gr = new TGraph(1000,sigAccEff,backRejEff);
	cout << "ROC Integral: " << gr->Integral() << endl;
	gr->SetLineColor(2);
	gr->SetLineWidth(2);
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(21);
	gr->SetTitle(rootName + " ROC Curve");
	gr->GetXaxis()->SetTitle("Signal Acceptance Efficiency");
	gr->GetYaxis()->SetTitle("Background Rejection Efficiency");
	gr->Draw("AC");
	c2->SaveAs(resultLoc + rootName + "_ROC_Curve.png");

}
