void DrawProfile(const Bool_t useSCmean = kTRUE, const Bool_t useSCFluc=kTRUE, const Bool_t isR=kTRUE, const Bool_t isRPhi = kFALSE, const Bool_t isZ=kFALSE);
void DrawProfileAll(){

	DrawProfile(kTRUE,kTRUE,kTRUE,kFALSE,kFALSE);
	DrawProfile(kTRUE,kTRUE,kFALSE,kTRUE,kFALSE);
	DrawProfile(kTRUE,kTRUE,kFALSE,kFALSE,kTRUE);

	DrawProfile(kFALSE,kTRUE,kTRUE,kFALSE,kFALSE);
	DrawProfile(kFALSE,kTRUE,kFALSE,kTRUE,kFALSE);
	DrawProfile(kFALSE,kTRUE,kFALSE,kFALSE,kTRUE);

}
//______________________________________________________________
void DrawProfile(const Bool_t useSCmean, const Bool_t useSCFluc, const Bool_t isR, const Bool_t isRPhi, const Bool_t isZ)
{
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);

	TCanvas *c1 = new TCanvas("c1","c1",0,0,800,800);
	c1->SetMargin(0.12,0.05,0.12,0.05);
	c1->SetTicks(1,1);

	TH1F *frame = (TH1F*)c1->DrawFrame(-6,-0.5,+6,+0.5);
	if(isR){
		frame->GetXaxis()->SetTitle("numerical fluctuation (cm), dr");
		frame->GetYaxis()->SetTitle("mean value of (pred. - num.) in 100 test events (cm), dr");
	}
	else if(isRPhi){
		frame->GetXaxis()->SetTitle("numerical fluctuation (cm), rd#varphi");
		frame->GetYaxis()->SetTitle("mean value of (pred. - num.) in 100 test events (cm), rd#varphi");
	}
	else if(isZ){
		frame->GetXaxis()->SetTitle("numerical fluctuation (cm), dz");
		frame->GetYaxis()->SetTitle("mean value of (pred. - num.) in 100 test events (cm), dz");
	}
	frame->GetXaxis()->SetTitleOffset(1.5);
	frame->GetYaxis()->SetTitleOffset(1.5);
	frame->GetXaxis()->CenterTitle(kTRUE);
	frame->GetYaxis()->CenterTitle(kTRUE);
	frame->GetXaxis()->SetTitleSize(0.035);
	frame->GetYaxis()->SetTitleSize(0.035);
	frame->GetXaxis()->SetLabelSize(0.035);
	frame->GetYaxis()->SetLabelSize(0.035);

	const Int_t Nev[] = {500,1000, 1500, 2000, 5000};
	const Int_t n = sizeof(Nev)/sizeof(Nev[0]);
	const Int_t color[n] = {kViolet+1, kBlue+1, kCyan+1, kTeal+2, kGreen+2};

	const TString str_param = Form("phi90_r17_z17_filter4_poo0_drop0.00_depth4_batch0_scaler0_useSCMean%d_useSCFluc%d_pred_doR%d_dophi%d_doz%d",useSCmean,useSCFluc,isR,isRPhi,isZ);

	TLegend *leg = new TLegend(0.7,0.5,0.9,0.9);
	leg->SetBorderSize(0);
	for(Int_t i=0;i<n;i++){
		TString filename = Form("validation/output%s_Nev%d.root",str_param.Data(),Nev[i]);
		printf("reading ... %s\n",filename.Data());

		TFile *rootfile = TFile::Open(filename,"READ");
		TProfile *h1prf = (TProfile*)rootfile->Get(Form("profiledeltasvsdistallevents%s_Nev%d",str_param.Data(),Nev[i]));
		h1prf->SetDirectory(0);
		h1prf->Draw("same");
		h1prf->SetMarkerStyle(20);
		h1prf->SetMarkerColor(color[i]);
		h1prf->SetLineColor(color[i]);

		leg->AddEntry(h1prf,Form("N_{ev}^{training} = %d",Nev[i]),"LP");
		rootfile->Close();

	}//end of Nev loop
	leg->Draw();

	TPaveText *txt1 = new TPaveText(0.2,0.8,0.4,0.9,"NDC");
	txt1->SetFillColor(kWhite);
	txt1->SetFillStyle(0);
	txt1->SetBorderSize(0);
	txt1->SetTextAlign(12);//middle,left
	txt1->SetTextFont(42);//helvetica
	txt1->SetTextSize(0.04);
	if(useSCFluc && useSCmean) txt1->AddText("inputs : #rho_{SC} - <#rho_{SC}>, <#rho_{SC}>");
	else if(useSCFluc) txt1->AddText("inputs : #rho_{SC} - <#rho_{SC}>");
	txt1->Draw();

	c1->SaveAs(Form("20200224_Fluc_MeanSC_Profile_%s.png",str_param.Data()));
	c1->SaveAs(Form("20200224_Fluc_MeanSC_Profile_%s.eps",str_param.Data()));
	c1->SaveAs(Form("20200224_Fluc_MeanSC_Profile_%s.pdf",str_param.Data()));
}
