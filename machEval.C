	
void machEval(TString inFile, TString rootName, TString methodology, int layer1, int layer2, TString realTreeName) {
	
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
	
	//TFile *input = TFile::Open(inFile);
	backinput->cd();
	TTree *simu = (TTree *) backinput->Get("background");
	
	
	
	Float_t mass, xF, xB, dx, dy, dz, dpx, dpy, dpz, costh, phi, px1, py1, pz1, px2, py2, pz2, trackSeparation, chisq_dimuon, xT, xD, yD, yT, pxD, pyD, pzD, pxT, pyT, pzT, thbend, x0, y0, z0, px0, py0, pz0, x3, px3, py3, pz3, x1, y1, px11, py11, pz11, chisq, chisq_dump, chisq_target, xT1, chisq_upstream, pzxT, pzyT, rD, normChi;
	//Float_t ptsumf, qelep, nch, msumf, minvis, acopl, acolin;
	Int_t type;
	
	simu->SetBranchAddress("mass", &mass, "mass/F");
	simu->SetBranchAddress("xF",  &xF,  "xF/F");
	simu->SetBranchAddress("xB",    &xB,    "xB/F");
	simu->SetBranchAddress("dx",  &dx,  "dx/F");
	simu->SetBranchAddress("dy",  &dy,  "dy/F");
	simu->SetBranchAddress("dz", &dz, "dz/F");
	simu->SetBranchAddress("dpx",  &dpx,  "dpx/F");
	simu->SetBranchAddress("dpy", &dpy, "dpy/F");
	simu->SetBranchAddress("dpz", &dpz, "dpz/F");
	simu->SetBranchAddress("costh", &costh, "costh/F");
	simu->SetBranchAddress("phi", &phi, "phi/F");
	simu->SetBranchAddress("px1", &px1, "px1/F");
	simu->SetBranchAddress("py1", &py1, "py1/F");
	simu->SetBranchAddress("pz1", &pz1, "pz1/F");
	simu->SetBranchAddress("px2", &px2, "px2/F");
	simu->SetBranchAddress("py2", &py2, "py2/F");
	simu->SetBranchAddress("pz2", &pz2, "pz2/F");
	simu->SetBranchAddress("trackSeparation", &trackSeparation, "trackSeparation/F");
	simu->SetBranchAddress("chisq_dimuon", &chisq_dimuon, "chisq_dimuon/F");
	simu->SetBranchAddress("xT", &xT, "xT/F");
	simu->SetBranchAddress("xD", &xD, "xD/F");
	simu->SetBranchAddress("yD", &yD, "yD/F");
	simu->SetBranchAddress("yT", &yT, "yT/F");
	simu->SetBranchAddress("pxD", &pxD, "pxD/F");
	simu->SetBranchAddress("pyD", &pyD, "pyD/F");
	simu->SetBranchAddress("pzD", &pzD, "pzD/F");
	simu->SetBranchAddress("pxT", &pxT, "pxT/F");
	simu->SetBranchAddress("pyT", &pyT, "pyT/F");
	simu->SetBranchAddress("pzT", &pzT, "pzT/F");
	simu->SetBranchAddress("thbend", &thbend, "thbend/F");
	simu->SetBranchAddress("x0", &x0, "x0/F");
	simu->SetBranchAddress("y0", &y0, "y0/F");
	simu->SetBranchAddress("z0", &z0, "z0/F");
	simu->SetBranchAddress("px0", &px0, "px0/F");
	simu->SetBranchAddress("py0", &py0, "py0/F");
	simu->SetBranchAddress("pz0", &pz0, "pz0/F");
	simu->SetBranchAddress("x3", &x3, "x3/F");
	simu->SetBranchAddress("px3", &px3, "px3/F");
	simu->SetBranchAddress("py3", &py3, "py3/F");
	simu->SetBranchAddress("pz3", &pz3, "pz3/F");
	simu->SetBranchAddress("x1", &x1, "x1/F");
	simu->SetBranchAddress("y1", &y1, "y1/F");
	simu->SetBranchAddress("px11", &px11, "px11/F");
	simu->SetBranchAddress("py11", &py11, "py11/F");
	simu->SetBranchAddress("pz11", &pz11, "pz11/F");
	simu->SetBranchAddress("chisq", &chisq, "chisq/F");
	simu->SetBranchAddress("chisq_dump", &chisq_dump, "chisq_dump/F");
	simu->SetBranchAddress("chisq_target", &chisq_target, "chisq_target/F");
	simu->SetBranchAddress("xT1", &xT1, "xT1/F"); 
	simu->SetBranchAddress("chisq_upstream", &chisq_upstream, "chisq_upstream/F");
	simu->SetBranchAddress("pzxT", &pzxT, "pzxT/F");
	simu->SetBranchAddress("pzyT", &pzyT, "pzyT/F");
	simu->SetBranchAddress("rD", &rD, "rD/F");
	simu->SetBranchAddress("normChi", &normChi, "normChi/F");
	simu->SetBranchAddress("type",   &type,   "type/I");
	
	
	type = 1;
	Int_t i;
	Int_t loopLim = 10000;

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
	
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	mlp->LoadWeights("./results/mu_70_mass_GC_LD2_mcR_mess_NsW_kT_kD_NC_SB_Batch_15_10/weighted_nn.txt");
	
	TString inFile2 = "./Trees2/mu_70_MixAll_kT_kD_NC.root";
	
	TString trees[1];
	//trees[0] = "signal";
	trees[0] = "background";
	
	TFile *input= new TFile(inFile2,"UPDATE");
	
	for (int e = 0; e < 1; e++) {
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
			cout << "Type: " << curType << endl;
			cout << branchVal << endl;
			branch->Fill();	cout << "After" << endl;
		}
		mainTree->ResetBranchAddresses();
		input->Write("",TObject::kOverwrite);
		
	}
	input->Close();
}