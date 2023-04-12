/*
	Author----------------------->John W. Rice
	Last Revision---------------->July/31/2017
	Depndencies------------------>varParser.C
*/

int multiVarParser() {
	
//##################################################################################################################
//                                           *** Load Needed Macros ***
//##################################################################################################################
	gROOT->LoadMacro("varParser.C");
	
//##################################################################################################################
//                                           *** Set Names To Be Used ***
//##################################################################################################################
	TString method[6];
	vector <TString> name;
	//name.push_back("./Trees2/mu_70_GC_LD2_3_mcR_mess_NsW_kT_kD_NC_SB.root");
	//name.push_back("./Trees2/mu_70_GC_LD2_Geo_mcR_mess_NsW_kT_kD_NC_SB.root");
	//name.push_back("./Trees2/mu_70_GC_LD2_mcR_mess_NsW_kT_kD_NC_SB.root");
	//name.push_back("./Trees2/mu_70_mass_GC_LD2_mcR_mess_NsW_kT_kD_NC_SB.root");
	//name.push_back("./Trees2/mu_70_Mix_LD2_mcR_mess_NsW_kT_kD_NC_SB.root");
	//name.push_back("./Trees2/mu_LD2_jpsi_dump_mcR_mess_NsW_kT_kD_NC_SB.root");
	name.push_back("./Trees2/mu_70_MixAll_kT_kD_NC.root");
	
//##################################################################################################################
//                               *** Run Parameters Through Neural Network ***
//##################################################################################################################
	for (int i = 0; i < name.size(); i++) {
		varParser(name[i]);
	}
	return 0;
}