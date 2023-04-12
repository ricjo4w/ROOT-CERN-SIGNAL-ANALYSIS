
void varParser(TString inFile) {
	vector <TString> trees;
	//trees.push_back("signal");
	trees.push_back("background");
	
	TFile *input= new TFile(inFile,"UPDATE");
	
	for (int e = 0; e < trees.size(); e++) {
		
		TTree *mainTree = (TTree *) input->Get(trees[e]);

		Float_t pzxT, pzyT, rD, normChi, xT1, pz11, yT, xD, yD, chisq, numHits;
		
		mainTree->SetBranchAddress("xT1", &xT1);
		mainTree->SetBranchAddress("pz11", &pz11);
		mainTree->SetBranchAddress("yT", &yT);
		mainTree->SetBranchAddress("xD", &xD);
		mainTree->SetBranchAddress("yD", &yD);
		mainTree->SetBranchAddress("chisq", &chisq);
		mainTree->SetBranchAddress("numHits", &numHits);
		
		TBranch *pzxTBranch =  mainTree->Branch("pzxT",&pzxT,"pzxT/F");
		TBranch *pzyTBranch =  mainTree->Branch("pzyT",&pzyT,"pzyT/F");
		TBranch *rDBranch =  mainTree->Branch("rD",&rD,"rD/F");
		TBranch *normChiBranch =  mainTree->Branch("normChi",&normChi,"normChi/F");
		
		for (int i = 0; i < mainTree->GetEntries(); i++) {
			mainTree->GetEntry(i);
			pzxT = xT1*pz11;
			pzyT = (yT - 1.6)*pz11;
			rD = sqrt(xD*xD + (yD - 1.6)*(yD - 1.6));
			normChi = chisq/(numHits - 5);
			pzxTBranch->Fill();
			pzyTBranch->Fill();
			rDBranch->Fill();
			normChiBranch->Fill();
		}
		input->Write("",TObject::kOverwrite);
	}
}