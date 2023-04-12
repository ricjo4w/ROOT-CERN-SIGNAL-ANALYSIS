/*
	Author----------------------->John W. Rice
	Last Revision---------------->July/24/2017
	Depndencies------------------>Grapher.C
*/

#include <TMultiLayerPerceptron.h>



void machRun(TString realFile, TString realName, TString realTreeName, TString inFile, TString rootName, TString methodology, int layer1, int layer2)
{
	//gROOT->Reset();
//################################################################################################################## 
//##################################################################################################################
	string folder = rootName + "_" + Form("%d",layer1) + "_" + Form("%d",layer2);
	float epochs = 600;
	float lim = 1000;
	
//##################################################################################################################
//                                             *** Set Method ***
//##################################################################################################################
	bool stochastic = false;
	bool batch = false;
	bool steepestDescent = false;
	bool ribierePolak = false;
	bool fletcherReeves = false;
	bool BFGS = false;
	
	if (methodology == "Stochastic") {
		stochastic = true;
	}
	if (methodology == "Batch") {
		batch = true;
	}
	if (methodology == "SteepestDesent") {
		steepestDescent = true;
	}
	if (methodology == "RibierePolak") {
		ribierePolak = true;
	}
	if (methodology == "FletcherReeves") {
		fletcherReeves = true;
	}
	if (methodology == "BFGS") {
		BFGS = true;
	}
	
//##################################################################################################################
//                                           *** Make Save Folder ***
//##################################################################################################################
	
	string folder = rootName + "_" + methodology + "_" + Form("%d",layer1) + "_" + Form("%d",layer2);
	
	
	string dir = "mkdir './results/";
	dir += folder;
	dir += "'";
	cout << "Directory: " << dir << endl;
	const char *cstr = dir.c_str();
	system(cstr);
	const TString resultLoc = "./results/" + folder + "/";
	
	
	string ofStreamDir = "mkdir './results/";
	ofStreamDir += folder;
	ofStreamDir += "/ofstreams'";
	const char *ofChar = ofStreamDir.c_str();
	system(ofChar);
	
	ofstream NNout(resultLoc + "ofstreams/" + rootName + "_NN.txt", std::ofstream::trunc);
	
//##################################################################################################################
//                                       *** Neural Network Arguments ***
//##################################################################################################################

	//Define the variables to be used.

	TString input0 = "mass, xF, xB, dx, dy, dz, dpx, dpy, dpz, costh, phi, px1, py1, pz1, px2, py2, pz2, trackSeparation, chisq_dimuon, xT, xD, yD, yT, pxD, pyD, pzD, pxT, pyT, pzT, thbend, x0, y0, z0, px0, py0, pz0, x3, px3, py3, pz3, x1, y1, px11, py11, pz11, chisq, chisq_dump, chisq_target, xT1, chisq_upstream, pzxT, pzyT, rD, normChi";
	//TString hiddenlayer1 = Form("%d",layer1);
	//TString hiddenlayer2 = Form("%d",layer2);
	TString hiddenlayer1 = Form("%d",layer1);
	TString hiddenlayer2 = Form("%d",layer2);
	TString output = "type";

	TString arg = input0;
	arg += ":" + hiddenlayer1;
	arg += ":" + hiddenlayer2;
	arg += ":" + output;
	cout << arg << endl;

//##################################################################################################################
//                                            *** Load TTree ***
//##################################################################################################################
	//TFile *siginput= new TFile(inFile,"UPDATE");
	//TFile *backinput= new TFile(inFile,"UPDATE");
	
	TFile *backinput= new TFile(inFile,"READ");
	TFile *siginput= new TFile(inFile,"READ");
	cout << "File is: " << inFile << endl;
	backinput->ls();
	
	TFile *saveFile = new TFile(rootName + ".root","RECREATE");
	TTree *simu = new TTree("tempTree", "Filtered TempTree Events");
	
	//TFile *input = TFile::Open(inFile);
	backinput->cd();
	TTree *bg_filtered = (TTree *) backinput->Get("background");
	
	siginput->cd();
	TTree *sig_filtered = (TTree *) siginput->Get("signal");
	
	
	
	Float_t mass, xF, xB, dx, dy, dz, dpx, dpy, dpz, costh, phi, px1, py1, pz1, px2, py2, pz2, trackSeparation, chisq_dimuon, xT, xD, yD, yT, pxD, pyD, pzD, pxT, pyT, pzT, thbend, x0, y0, z0, px0, py0, pz0, x3, px3, py3, pz3, x1, y1, px11, py11, pz11, chisq, chisq_dump, chisq_target, xT1, chisq_upstream, pzxT, pzyT, rD, normChi;
	//Float_t ptsumf, qelep, nch, msumf, minvis, acopl, acolin;
	Int_t type;
	
	sig_filtered->SetBranchAddress("mass", &mass);
	sig_filtered->SetBranchAddress("xF",  &xF);
	sig_filtered->SetBranchAddress("xB",    &xB);
	sig_filtered->SetBranchAddress("dx",  &dx);
	sig_filtered->SetBranchAddress("dy",  &dy);
	sig_filtered->SetBranchAddress("dz", &dz);
	sig_filtered->SetBranchAddress("dpx",  &dpx);
	sig_filtered->SetBranchAddress("dpy", &dpy);
	sig_filtered->SetBranchAddress("dpz", &dpz);
	sig_filtered->SetBranchAddress("costh", &costh);
	sig_filtered->SetBranchAddress("phi", &phi);
	sig_filtered->SetBranchAddress("px1", &px1);
	sig_filtered->SetBranchAddress("py1", &py1);
	sig_filtered->SetBranchAddress("pz1", &pz1);
	sig_filtered->SetBranchAddress("px2", &px2);
	sig_filtered->SetBranchAddress("py2", &py2);
	sig_filtered->SetBranchAddress("pz2", &pz2);
	sig_filtered->SetBranchAddress("trackSeparation", &trackSeparation);
	sig_filtered->SetBranchAddress("chisq_dimuon", &chisq_dimuon);
	sig_filtered->SetBranchAddress("xT", &xT);
	sig_filtered->SetBranchAddress("xD", &xD);
	sig_filtered->SetBranchAddress("yD", &yD);
	sig_filtered->SetBranchAddress("yT", &yT);
	sig_filtered->SetBranchAddress("pxD", &pxD);
	sig_filtered->SetBranchAddress("pyD", &pyD);
	sig_filtered->SetBranchAddress("pzD", &pzD);
	sig_filtered->SetBranchAddress("pxT", &pxT);
	sig_filtered->SetBranchAddress("pyT", &pyT);
	sig_filtered->SetBranchAddress("pzT", &pzT);
	sig_filtered->SetBranchAddress("thbend", &thbend);
	sig_filtered->SetBranchAddress("x0", &x0);
	sig_filtered->SetBranchAddress("y0", &y0);
	sig_filtered->SetBranchAddress("z0", &z0);
	sig_filtered->SetBranchAddress("px0", &px0);
	sig_filtered->SetBranchAddress("py0", &py0);
	sig_filtered->SetBranchAddress("pz0", &pz0);
	sig_filtered->SetBranchAddress("x3", &x3);
	sig_filtered->SetBranchAddress("px3", &px3);
	sig_filtered->SetBranchAddress("py3", &py3);
	sig_filtered->SetBranchAddress("pz3", &pz3);
	sig_filtered->SetBranchAddress("x1", &x1);
	sig_filtered->SetBranchAddress("y1", &y1);
	sig_filtered->SetBranchAddress("px11", &px11);
	sig_filtered->SetBranchAddress("py11", &py11);
	sig_filtered->SetBranchAddress("pz11", &pz11);
	sig_filtered->SetBranchAddress("chisq", &chisq);
	sig_filtered->SetBranchAddress("chisq_dump", &chisq_dump);
	sig_filtered->SetBranchAddress("chisq_target", &chisq_target);
	sig_filtered->SetBranchAddress("xT1", &xT1);
	sig_filtered->SetBranchAddress("chisq_upstream", &chisq_upstream);
	sig_filtered->SetBranchAddress("pzxT", &pzxT);
	sig_filtered->SetBranchAddress("pzyT", &pzyT);
	sig_filtered->SetBranchAddress("rD", &rD);
	sig_filtered->SetBranchAddress("normChi", &normChi);
	
	
	bg_filtered->SetBranchAddress("mass", &mass);
	bg_filtered->SetBranchAddress("xF",  &xF);
	bg_filtered->SetBranchAddress("xB",    &xB);
	bg_filtered->SetBranchAddress("dx",  &dx);
	bg_filtered->SetBranchAddress("dy",  &dy);
	bg_filtered->SetBranchAddress("dz", &dz);
	bg_filtered->SetBranchAddress("dpx",  &dpx);
	bg_filtered->SetBranchAddress("dpy", &dpy);
	bg_filtered->SetBranchAddress("dpz", &dpz);
	bg_filtered->SetBranchAddress("costh", &costh);
	bg_filtered->SetBranchAddress("phi", &phi);
	bg_filtered->SetBranchAddress("px1", &px1);
	bg_filtered->SetBranchAddress("py1", &py1);
	bg_filtered->SetBranchAddress("pz1", &pz1);
	bg_filtered->SetBranchAddress("px2", &px2);
	bg_filtered->SetBranchAddress("py2", &py2);
	bg_filtered->SetBranchAddress("pz2", &pz2);
	bg_filtered->SetBranchAddress("trackSeparation", &trackSeparation);
	bg_filtered->SetBranchAddress("chisq_dimuon", &chisq_dimuon);
	bg_filtered->SetBranchAddress("xT", &xT);
	bg_filtered->SetBranchAddress("xD", &xD);
	bg_filtered->SetBranchAddress("yD", &yD);
	bg_filtered->SetBranchAddress("yT", &yT);
	bg_filtered->SetBranchAddress("pxD", &pxD);
	bg_filtered->SetBranchAddress("pyD", &pyD);
	bg_filtered->SetBranchAddress("pzD", &pzD);
	bg_filtered->SetBranchAddress("pxT", &pxT);
	bg_filtered->SetBranchAddress("pyT", &pyT);
	bg_filtered->SetBranchAddress("pzT", &pzT);
	bg_filtered->SetBranchAddress("thbend", &thbend);
	bg_filtered->SetBranchAddress("x0", &x0);
	bg_filtered->SetBranchAddress("y0", &y0);
	bg_filtered->SetBranchAddress("z0", &z0);
	bg_filtered->SetBranchAddress("px0", &px0);
	bg_filtered->SetBranchAddress("py0", &py0);
	bg_filtered->SetBranchAddress("pz0", &pz0);
	bg_filtered->SetBranchAddress("x3", &x3);
	bg_filtered->SetBranchAddress("px3", &px3);
	bg_filtered->SetBranchAddress("py3", &py3);
	bg_filtered->SetBranchAddress("pz3", &pz3);
	bg_filtered->SetBranchAddress("x1", &x1);
	bg_filtered->SetBranchAddress("y1", &y1);
	bg_filtered->SetBranchAddress("px11", &px11);
	bg_filtered->SetBranchAddress("py11", &py11);
	bg_filtered->SetBranchAddress("pz11", &pz11);
	bg_filtered->SetBranchAddress("chisq", &chisq);
	bg_filtered->SetBranchAddress("chisq_dump", &chisq_dump);
	bg_filtered->SetBranchAddress("chisq_target", &chisq_target);
	bg_filtered->SetBranchAddress("xT1", &xT1); 
	bg_filtered->SetBranchAddress("chisq_upstream", &chisq_upstream);
	bg_filtered->SetBranchAddress("pzxT", &pzxT);
	bg_filtered->SetBranchAddress("pzyT", &pzyT);
	bg_filtered->SetBranchAddress("rD", &rD);
	bg_filtered->SetBranchAddress("normChi", &normChi);
	
	simu->Branch("mass", &mass, "mass/F");
	simu->Branch("xF",  &xF,  "xF/F");
	simu->Branch("xB",    &xB,    "xB/F");
	simu->Branch("dx",  &dx,  "dx/F");
	simu->Branch("dy",  &dy,  "dy/F");
	simu->Branch("dz", &dz, "dz/F");
	simu->Branch("dpx",  &dpx,  "dpx/F");
	simu->Branch("dpy", &dpy, "dpy/F");
	simu->Branch("dpz", &dpz, "dpz/F");
	simu->Branch("costh", &costh, "costh/F");
	simu->Branch("phi", &phi, "phi/F");
	simu->Branch("px1", &px1, "px1/F");
	simu->Branch("py1", &py1, "py1/F");
	simu->Branch("pz1", &pz1, "pz1/F");
	simu->Branch("px2", &px2, "px2/F");
	simu->Branch("py2", &py2, "py2/F");
	simu->Branch("pz2", &pz2, "pz2/F");
	simu->Branch("trackSeparation", &trackSeparation, "trackSeparation/F");
	simu->Branch("chisq_dimuon", &chisq_dimuon, "chisq_dimuon/F");
	simu->Branch("xT", &xT, "xT/F");
	simu->Branch("xD", &xD, "xD/F");
	simu->Branch("yD", &yD, "yD/F");
	simu->Branch("yT", &yT, "yT/F");
	simu->Branch("pxD", &pxD, "pxD/F");
	simu->Branch("pyD", &pyD, "pyD/F");
	simu->Branch("pzD", &pzD, "pzD/F");
	simu->Branch("pxT", &pxT, "pxT/F");
	simu->Branch("pyT", &pyT, "pyT/F");
	simu->Branch("pzT", &pzT, "pzT/F");
	simu->Branch("thbend", &thbend, "thbend/F");
	simu->Branch("x0", &x0, "x0/F");
	simu->Branch("y0", &y0, "y0/F");
	simu->Branch("z0", &z0, "z0/F");
	simu->Branch("px0", &px0, "px0/F");
	simu->Branch("py0", &py0, "py0/F");
	simu->Branch("pz0", &pz0, "pz0/F");
	simu->Branch("x3", &x3, "x3/F");
	simu->Branch("px3", &px3, "px3/F");
	simu->Branch("py3", &py3, "py3/F");
	simu->Branch("pz3", &pz3, "pz3/F");
	simu->Branch("x1", &x1, "x1/F");
	simu->Branch("y1", &y1, "y1/F");
	simu->Branch("px11", &px11, "px11/F");
	simu->Branch("py11", &py11, "py11/F");
	simu->Branch("pz11", &pz11, "pz11/F");
	simu->Branch("chisq", &chisq, "chisq/F");
	simu->Branch("chisq_dump", &chisq_dump, "chisq_dump/F");
	simu->Branch("chisq_target", &chisq_target, "chisq_target/F");
	simu->Branch("xT1", &xT1, "xT1/F"); 
	simu->Branch("chisq_upstream", &chisq_upstream, "chisq_upstream/F");
	simu->Branch("pzxT", &pzxT, "pzxT/F");
	simu->Branch("pzyT", &pzyT, "pzyT/F");
	simu->Branch("rD", &rD, "rD/F");
	simu->Branch("normChi", &normChi, "normChi/F");
	simu->Branch("type",   &type,   "type/I");
	
	
	type = 1;
	Int_t i;
	Int_t loopLim = 10000;
	for (i = 0; i < sig_filtered->GetEntries(); i++) {
	//for (i = 0; i < loopLim; i++) {
      sig_filtered->GetEntry(i);
      simu->Fill();
   }
	type = 0;
	for (i = 0; i < bg_filtered->GetEntries(); i++) {	//<--For entire tree
	//for (i = 0; i < loopLim; i++) {	//<--For partial tree
      bg_filtered->GetEntry(i);
      simu->Fill();
   }
	bg_filtered->ResetBranchAddresses();
	sig_filtered->ResetBranchAddresses();

//##################################################################################################################
//                                            *** Neural Network ***
//##################################################################################################################
	TMultiLayerPerceptron* mlp=new TMultiLayerPerceptron(arg,simu,"Entry$ %2 == 1","Entry$ %2 == 0");
	if (stochastic) mlp->SetLearningMethod(TMultiLayerPerceptron::kStochastic);
	if (batch) mlp->SetLearningMethod(TMultiLayerPerceptron::kBatch);
	if (steepestDescent) mlp->SetLearningMethod(TMultiLayerPerceptron::kSteepestDescent);
	if (ribierePolak) mlp->SetLearningMethod(TMultiLayerPerceptron::kRibierePolak);
	if (fletcherReeves) mlp->SetLearningMethod(TMultiLayerPerceptron::kFletcherReeves);
	if (BFGS) mlp->SetLearningMethod(TMultiLayerPerceptron::kBFGS);

//##################################################################################################################
//                                       *** Analyze and Draw Results ***
//##################################################################################################################
	c1 = new TCanvas("c1", "jtrack NN", 800, 800);
	c1->Divide(2, 2);

	c1->cd(1);
	mlp->Train(epochs, "text current graph update=1");

	TMLPAnalyzer* mlpa=new TMLPAnalyzer(mlp);
	mlpa->GatherInformations();
	mlpa->CheckNetwork();

	c1->cd(2);
	mlp->Draw();

	c1->cd(3);
	mlpa->DrawDInputs();

	c1->cd(4);
	mlpa->DrawNetwork(0, output + " == 1", output + " == 0");

//##################################################################################################################
//                                            *** Save Results ***
//##################################################################################################################
	TString savename = rootName + "_NN";
	savename += "_" + hiddenlayer1;
	savename += "_" + hiddenlayer2;
	savename += ".png";
	c1->SaveAs(resultLoc + savename);
	mlp->DumpWeights(resultLoc + "weighted_nn.txt");
	
	
	backinput->Close();
	//siginput->Close();
//##################################################################################################################
//                                            *** Clear ROOT Files ***
//##################################################################################################################
	saveFile->Write();
	saveFile->Close();
	//delete saveFile;
	delete siginput;
	delete backinput;
	
//##################################################################################################################
//                                              *** Graph Results ***
//##################################################################################################################
	
	//Grapher(rootName, inFile, lim, resultLoc);
	//Grapher(rootName, resultLoc + "nnResult.root", lim, resultLoc);
	
	
	TString inFile2 = "./Trees2/mu_70_GC_LD2_3_mcR_mess_NsW_kT_kD_NC_SB.root";
	
	TString trees[2];
	trees[0] = "signal";
	trees[1] = "background";
	
	TFile *input= new TFile(inFile,"UPDATE");
	
	for (int e = 0; e < 2; e++) {
		input->cd();
		TTree *mainTree = (TTree *) input->Get(trees[e]);
		TString curType = trees[e];
		Float_t mass5, xF5, xB5, dx5, dy5, dz5, dpx5, dpy5, dpz5, costh5, phi5, px15, py15, pz15, px25, py25, pz25, trackSeparation5, chisq_dimuon5, xT5, xD5, yD5, yT5, pxD5, pyD5, pzD5, pxT5, pyT5, pzT5, thbend5, x05, y05, z05, px05, py05, pz05, x35, px35, py35, pz35, x15, y15, px115, py115, pz115, chisq5, chisq_dump5, chisq_target5, xT15, chisq_upstream5, branchVal;
		Float_t pzxT5, pzyT5, rD5, normChi5;
		mainTree->SetBranchAddress("mass", &mass5);
		mainTree->SetBranchAddress("xF",  &xF5);
		mainTree->SetBranchAddress("xB",    &xB5);
		mainTree->SetBranchAddress("dx",  &dx5);
		mainTree->SetBranchAddress("dy",  &dy5);
		mainTree->SetBranchAddress("dz", &dz5);
		mainTree->SetBranchAddress("dpx",  &dpx5);
		mainTree->SetBranchAddress("dpy", &dpy5);
		mainTree->SetBranchAddress("dpz", &dpz5);
		mainTree->SetBranchAddress("costh", &costh5);
		mainTree->SetBranchAddress("phi", &phi5);
		mainTree->SetBranchAddress("px1", &px15);
		mainTree->SetBranchAddress("py1", &py15);
		mainTree->SetBranchAddress("pz1", &pz15);
		mainTree->SetBranchAddress("px2", &px25);
		mainTree->SetBranchAddress("py2", &py25);
		mainTree->SetBranchAddress("pz2", &pz25);
		mainTree->SetBranchAddress("trackSeparation", &trackSeparation5);
		mainTree->SetBranchAddress("chisq_dimuon", &chisq_dimuon5);
		mainTree->SetBranchAddress("xT", &xT5);
		mainTree->SetBranchAddress("xD", &xD5);
		mainTree->SetBranchAddress("yD", &yD5);
		mainTree->SetBranchAddress("yT", &yT5);
		mainTree->SetBranchAddress("pxD", &pxD5);
		mainTree->SetBranchAddress("pyD", &pyD5);
		mainTree->SetBranchAddress("pzD", &pzD5);
		mainTree->SetBranchAddress("pxT", &pxT5);
		mainTree->SetBranchAddress("pyT", &pyT5);
		mainTree->SetBranchAddress("pzT", &pzT5);
		mainTree->SetBranchAddress("thbend", &thbend5);
		mainTree->SetBranchAddress("x0", &x05);
		mainTree->SetBranchAddress("y0", &y05);
		mainTree->SetBranchAddress("z0", &z05);
		mainTree->SetBranchAddress("px0", &px05);
		mainTree->SetBranchAddress("py0", &py05);
		mainTree->SetBranchAddress("pz0", &pz05);
		mainTree->SetBranchAddress("x3", &x35);
		mainTree->SetBranchAddress("px3", &px35);
		mainTree->SetBranchAddress("py3", &py35);
		mainTree->SetBranchAddress("pz3", &pz35);
		mainTree->SetBranchAddress("x1", &x15);
		mainTree->SetBranchAddress("y1", &y15);
		mainTree->SetBranchAddress("px11", &px115);
		mainTree->SetBranchAddress("py11", &py115);
		mainTree->SetBranchAddress("pz11", &pz115);
		mainTree->SetBranchAddress("chisq", &chisq5);
		mainTree->SetBranchAddress("chisq_dump", &chisq_dump5);
		mainTree->SetBranchAddress("chisq_target", &chisq_target5);
		mainTree->SetBranchAddress("xT1", &xT15);
		mainTree->SetBranchAddress("pzxT", &pzxT5);
		mainTree->SetBranchAddress("pzyT", &pzyT5);
		mainTree->SetBranchAddress("rD", &rD5);
		mainTree->SetBranchAddress("normChi", &normChi5);
		mainTree->SetBranchAddress("chisq_upstream", &chisq_upstream5);
		
		TBranch *branch =  mainTree->Branch("nnResponse",&branchVal,"nnResponse/F");
		Double_t params[54];
		cout << "Line 96" << endl;
		for (i = 0; i < mainTree->GetEntries(); i++) {
			mainTree->GetEntry(i);
			params[0] = mass5;
			params[1] = xF5;
			params[2] = xB5;
			params[3] = dx5;
			params[4] = dy5;
			params[5] = dz5;
			params[6] = dpx5;
			params[7] = dpy5;
			params[8] = dpz5;
			params[9] = costh5;
			params[10] = phi5;
			params[11] = px15;
			params[12] = py15;
			params[13] = pz15;
			params[14] = px25;
			params[15] = py25;
			params[16] = pz25;
			params[17] = trackSeparation5;
			params[18] = chisq_dimuon5;
			params[19] = xT5;
			params[20] = xD5;
			params[21] = yD5;
			params[22] = yT5;
			params[23] = pxD5;
			params[24] = pyD5;
			params[25] = pzD5;
			params[26] = pxT5;
			params[27] = pyT5;
			params[28] = pzT5;
			params[29] = thbend5;
			params[30] = x05;
			params[31] = y05;
			params[32] = z05;
			params[33] = px05;
			params[34] = py05;
			params[35] = pz05;
			params[36] = x35;
			params[37] = px35;
			params[38] = py35;
			params[39] = pz35;
			params[40] = x15;
			params[41] = y15;
			params[42] = px115;
			params[43] = py115;
			params[44] = pz115;
			params[45] = chisq5;
			params[46] = chisq_dump5;
			params[47] = chisq_target5;
			params[48] = xT15;
			params[49] = chisq_upstream5;
			params[50] = pzxT5;
			params[51] = pzyT5;
			params[52] = rD5;
			params[53] = normChi5;
			
			branchVal = mlp->Evaluate(0, params);
			NNout << "response: " << branchVal << endl;
			cout << "Type: " << curType << endl;
			cout << branchVal << endl;
			branch->Fill();	cout << "After" << endl;
		}
		mainTree->ResetBranchAddresses();
		input->Write("",TObject::kOverwrite);
		
	}
	input->Close();
	cout << "DONE!" << endl;
	Grapher(rootName, inFile, lim, resultLoc);
	machEval(realFile, realName, methodology, layer1, layer2, realTreeName);
}