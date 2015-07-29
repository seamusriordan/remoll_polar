#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

void symmapdisplay() {
	
	// Graphics initialization
	//

	TCanvas *cBphi = new TCanvas("cBphi", "",491,189,700,502);
	cBphi->SetHighLightColor(2);
	cBphi->Range(-0.8421627,-0.9582822,0.8421627,0.9582822);
	TView *view = TView::CreateView(1);
	view->SetRange(-1,-1,-7.367216e-05,801,50,8.970953e-05);
	cBphi->SetFillColor(0);
	cBphi->SetBorderMode(0);
	cBphi->SetBorderSize(2);
	cBphi->SetTheta(19.17722);
	cBphi->SetPhi(-10.60345);
	cBphi->SetFrameBorderMode(0);

	TCanvas *cBr = new TCanvas("cBr", "",49,52,700,502);
	cBr->SetHighLightColor(2);
	cBr->Range(-0.8884543,-1.044525,0.8884543,1.044525);
	TView *view = TView::CreateView(1);
	view->SetRange(-1,-1,-0.243346,801,50,5.121616);
	cBr->SetFillColor(0);
	cBr->SetBorderMode(0);
	cBr->SetBorderSize(2);
	cBr->SetTheta(26.77215);
	cBr->SetPhi(-15.51724);
	cBr->SetFrameBorderMode(0);
   	
	TCanvas *cBz = new TCanvas("cBz", "",401,189,700,502);
	cBz->SetHighLightColor(2);
	cBz->Range(-0.8697405,-0.9634467,0.8697405,0.9634467);
	TView *view = TView::CreateView(1);
	view->SetRange(-1,-1,0,801,50,8.834574);
	cBz->SetFillColor(0);
	cBz->SetBorderMode(0);
	cBz->SetBorderSize(2);
	cBz->SetTheta(18.79747);
	cBz->SetPhi(-13.44828);
	cBz->SetFrameBorderMode(0);
   
	TH2F *hBphi = new TH2F("hBphi","Phi field component",400,-400,400,24,-1,50);
	TH2F *hBr = new TH2F("hBr","R field component",400,-400,400,24,-1,50);
	TH2F *hBz = new TH2F("hBz","Z field component",400,-400,400,24,-1,50);


	// Fill the histograms
	//	
	
	float par1, par2, par3, par4, par5, par6;
	
	ifstream infile;
	infile.open("/home/cameronc/gitdir/remoll_polar/Map.dat",ios::in );
	
	if (!infile.is_open()) {cout<< "error, file not opened"<<endl; return 1;}

	float junk1,junk2,junk3;
	infile >> junk1 >> junk2 >> junk3;
	infile >> junk1 >> junk2 >> junk3;
	infile >> junk1 >> junk2 >> junk3;
	infile >> junk1 >> junk2;
	infile >> junk1;
	infile >> junk1;
	//               R       Phi     Z       B_r     B_phi   B_z
	while( infile >> par1 >> par2 >> par3 >> par4 >> par5 >> par6 ){
		par1=(par1*500.0);
		par3=(par3*499.9)+201.;
		if (par1==25){
			par4=0;
			par5=0;
			par6=0;
		}
		cout<<par1<<"\t"<<par2<<"\t"<<par3<<"\t"<<par4<<"\t"<<par5<<"\t"<<par6<<endl;
		if (par2==180){
			hBz->SetBinContent(hBz->GetBin((int)par3,(int)par1),par6);
			hBr->SetBinContent(hBr->GetBin((int)par3,(int)par1),par4);
			hBphi->SetBinContent(hBphi->GetBin((int)par3,(int)par1),par5);
		/*
			if ((par5 < 1e-4) && (par5 > -1e-4)){
				hBphi->SetBinContent(hBphi->GetBin((int)par3,(int)par1),par5);
			}
			else {
				hBphi->SetBinContent(hBphi->GetBin((int)par3,(int)par1),0.00);
			}
		*/
		}
	}
	infile.close();


	// Edit the axis of the plots and print them
	//
	
//	hBz->SetEntries(20852);
	hBz->SetStats(0);
//	hBr->SetEntries(20852);
	hBr->SetStats(0);
//	hBphi->SetEntries(20852);
	hBphi->SetStats(0);
	
	
	Int_t ci;
	ci = TColor::GetColor("#000099");

	cBz->cd();
	hBz->SetLineColor(ci);
	hBz->GetXaxis()->SetTitle(" z/mm");
	hBz->GetXaxis()->SetLabelFont(42);
	hBz->GetXaxis()->SetLabelSize(0.035);
	hBz->GetXaxis()->SetTitleSize(0.035);
	hBz->GetXaxis()->SetTitleOffset(1.3);
	hBz->GetXaxis()->SetTitleFont(42);
	hBz->GetYaxis()->SetTitle(" r/mm");
	hBz->GetYaxis()->SetLabelFont(42);
	hBz->GetYaxis()->SetLabelSize(0.035);
	hBz->GetYaxis()->SetTitleSize(0.035);
	hBz->GetYaxis()->SetTitleOffset(1.5);
	hBz->GetYaxis()->SetTitleFont(42);
	hBz->GetZaxis()->SetTitle(" B_{z}/T");
	hBz->GetZaxis()->SetLabelFont(42);
	hBz->GetZaxis()->SetLabelSize(0.035);
	hBz->GetZaxis()->SetTitleSize(0.035);
	hBz->GetZaxis()->SetTitleFont(42);
	hBz->Draw("surf1");
	cBz->Modified();
	cBz->cd();
	cBz->SetSelected(cBz);
	cBz->Print(".symMap.pdf","pdf");

	cBr->cd();
	hBr->SetLineColor(ci);
	hBr->GetXaxis()->SetTitle(" z/mm");
	hBr->GetXaxis()->SetLabelFont(42);
	hBr->GetXaxis()->SetLabelSize(0.035);
	hBr->GetXaxis()->SetTitleSize(0.035);
	hBr->GetXaxis()->SetTitleOffset(1.3);
	hBr->GetXaxis()->SetTitleFont(42);
	hBr->GetYaxis()->SetTitle(" r/mm");
	hBr->GetYaxis()->SetLabelFont(42);
	hBr->GetYaxis()->SetLabelSize(0.035);
	hBr->GetYaxis()->SetTitleSize(0.035);
	hBr->GetYaxis()->SetTitleOffset(1.5);
	hBr->GetYaxis()->SetTitleFont(42);
	hBr->GetZaxis()->SetTitle(" B_{r}/T");
	hBr->GetZaxis()->SetLabelFont(42);
	hBr->GetZaxis()->SetLabelSize(0.035);
	hBr->GetZaxis()->SetTitleSize(0.035);
	hBr->GetZaxis()->SetTitleFont(42);
	hBr->Draw("surf1");
	cBr->Modified();
	cBr->cd();
	cBr->SetSelected(cBr);
	cBr->Print(".symMap.pdf","pdf");

	cBphi->cd();
	hBphi->SetLineColor(ci);
	hBphi->GetXaxis()->SetTitle(" z/mm");
	hBphi->GetXaxis()->SetLabelFont(42);
	hBphi->GetXaxis()->SetLabelSize(0.035);
	hBphi->GetXaxis()->SetTitleSize(0.035);
	hBphi->GetXaxis()->SetTitleOffset(1.3);
	hBphi->GetXaxis()->SetTitleFont(42);
	hBphi->GetYaxis()->SetTitle(" r/mm");
	hBphi->GetYaxis()->SetLabelFont(42);
	hBphi->GetYaxis()->SetLabelSize(0.035);
	hBphi->GetYaxis()->SetTitleSize(0.035);
	hBphi->GetYaxis()->SetTitleOffset(1.5);
	hBphi->GetYaxis()->SetTitleFont(42);
	hBphi->GetZaxis()->SetTitle(" B_{phi}/T");
	hBphi->GetZaxis()->SetLabelFont(42);
	hBphi->GetZaxis()->SetLabelSize(0.035);
	hBphi->GetZaxis()->SetTitleSize(0.035);
	hBphi->GetZaxis()->SetTitleFont(42);
	hBphi->Draw("surf1");
	cBphi->Modified();
	cBphi->cd();
	cBphi->SetSelected(cBphi);
	cBphi->Print(".symMap.pdf","pdf");
	
	return 0;
}
