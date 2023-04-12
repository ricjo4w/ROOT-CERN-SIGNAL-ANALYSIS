#include "machEval.C"

int multiEval() {
	
//##################################################################################################################
//                                           *** Load Needed Macros ***
//##################################################################################################################
	gROOT->LoadMacro("Grapher.C");
	gROOT->LoadMacro("machRun.C");
	//gROOT->LoadMacro("machEval.C");
	
//##################################################################################################################
//                                            *** Set Output Stream ***
//##################################################################################################################
	ofstream outCur("Progress.txt");
	
//##################################################################################################################
//                                              *** Set Parameters ***
//##################################################################################################################
	TString file;
	//file = "./Trees2/mu_70_GC_LD2_3_mcR_mess_NsW_kT_kD_NC_SB.root";
	//file = "./Trees2/mu_70_GC_LD2_Geo_mcR_mess_NsW_kT_kD_NC_SB.root";
	//file = "./Trees2/mu_70_GC_LD2_mcR_mess_NsW_kT_kD_NC_SB.root";
	file = "./Trees2/mu_70_mass_GC_LD2_mcR_mess_NsW_kT_kD_NC_SB.root";
	//file = "./Trees2/mu_70_Mix_LD2_mcR_mess_NsW_kT_kD_NC_SB.root";
	//file = "./Trees2/mu_LD2_jpsi_dump_mcR_mess_NsW_kT_kD_NC_SB.root";
	TString name;
	//name = "mu_70_GC_LD2_3_mcR_mess_NsW_kT_kD_NC_SB";
	//name = "mu_70_GC_LD2_Geo_mcR_mess_NsW_kT_kD_NC_SB";
	//name = "mu_70_GC_LD2_mcR_mess_NsW_kT_kD_NC_SB";
	name = "mu_70_mass_GC_LD2_mcR_mess_NsW_kT_kD_NC_SB";
	//name = "mu_70_Mix_LD2_mcR_mess_NsW_kT_kD_NC_SB";
	//name = "mu_LD2_jpsi_dump_mcR_mess_NsW_kT_kD_NC_SB";
	int neuronnumber1lower=	10;			//enter the first number of neurons 
	int neuronnumber1upper=	6;			//enter the first number of neurons 
	int neuronnumber2lower=	10;			//enter the second number of neurons
	int neuronnumber2upper=	6;			//enter the second number of neurons
	
//##################################################################################################################
//                                        *** Set Methods To Be Used ***
//##################################################################################################################
	TString method[6];
	method[0] = "Batch";
	method[1] = "FletcherReeves";
	method[2] = "Stochastic";
	method[3] = "SteepestDesent";
	method[4] = "RibierePolak";
	method[5] = "BFGS";
	
//##################################################################################################################
//                               *** Run Parameters Through Neural Network ***
//##################################################################################################################
	/*for (int e = 0; e < 1; e++) {
		TString curMethod = method[e];
		
		for (int i = neuronnumber1lower; i < neuronnumber1upper; i++) {
			int curNeuro1 = i;
			for (int ii = neuronnumber2lower; ii < neuronnumber2upper; ii++) {
				outCur << curMethod << endl
				outCur << curNeuro1 << endl;
				outCur << ii << endl;
				outCur.clear();
				machRun(file, name, curMethod, curNeuro1, ii);
			}
		}
	}*/
	machEval(file, name, "Batch", 15, 10);
	return 0;
}