#include <TFile.h>
#include <TROOT.h>
#include <TLegend.h>
#define PI 3.14159265
#define mec 5.109989E-4
#define hc 1.239842E-6

//gStyle->SetOptStat(0);
gROOT->SetStyle("Plain");
gStyle->SetFillColor(10);
gStyle->SetFrameBorderSize(0);
gStyle->SetStatStyle(0);
gStyle->SetTitleStyle(0); 
gROOT->ForceStyle();

void readfile(char *filename){
  
  TObjArray Hlist(0);

  TFile *fin = new TFile(filename);
  TTree *t1 = (TTree *) fin->Get("T");

  Int_t ev_pid;
  TBranch *b_ev_pid;
  t1->SetBranchAddress("ev.pid",&ev_pid, &b_ev_pid);
  Double_t ev_vx;
  TBranch *b_ev_vx;
  t1->SetBranchAddress("ev.vx",&ev_vx, &b_ev_vx);
  Double_t ev_vy;
  TBranch *b_ev_vy;
  t1->SetBranchAddress("ev.vy",&ev_vy, &b_ev_vy);
  Double_t ev_vz;
  TBranch *b_ev_vz;
  t1->SetBranchAddress("ev.vz",&ev_vz, &b_ev_vz);
  Double_t ev_p;
  TBranch *b_ev_p;
  t1->SetBranchAddress("ev.p",&ev_p, &b_ev_p);
  Double_t ev_px;
  TBranch *b_ev_px;
  t1->SetBranchAddress("ev.px",&ev_px, &b_ev_px);
  Double_t ev_py;
  TBranch *b_ev_py;
  t1->SetBranchAddress("ev.py",&ev_py, &b_ev_py);
  Double_t ev_pz;
  TBranch *b_ev_pz;
  t1->SetBranchAddress("ev.pz",&ev_pz, &b_ev_pz);
  Double_t ev_kine;
  TBranch *b_ev_kine;
  t1->SetBranchAddress("ev.kine",&ev_kine, &b_ev_kine);   
  Int_t hit_n;
  TBranch *b_hit_n;
  t1->SetBranchAddress("hit.n",&hit_n, &b_hit_n);
  Int_t hit_pe;
  TBranch *b_hit_pe;
  t1->SetBranchAddress("hit.pe",&hit_pe, &b_hit_pe);
  Int_t hit_det[25000];
  TBranch *b_hit_det;
  t1->SetBranchAddress("hit.det",&hit_det, &b_hit_det);
  Int_t hit_vid[25000];
  TBranch *b_hit_vid;
  t1->SetBranchAddress("hit.vid",&hit_vid, &b_hit_vid);
  Int_t hit_pid[25000];
  TBranch *b_hit_pid;
  t1->SetBranchAddress("hit.pid",&hit_pid, &b_hit_pid);
  Int_t hit_trid[25000];
  TBranch *b_hit_trid;
  t1->SetBranchAddress("hit.trid",&hit_trid, &b_hit_trid);
  Int_t hit_mtrid[25000];
  TBranch *b_hit_mtrid;
  t1->SetBranchAddress("hit.mtrid",&hit_mtrid, &b_hit_mtrid);
  Int_t hit_gen[25000];
  TBranch *b_hit_gen;
  t1->SetBranchAddress("hit.gen",&hit_gen, &b_hit_gen);
  Double_t hit_x[25000];
  TBranch *b_hit_x;
  t1->SetBranchAddress("hit.x",&hit_x, &b_hit_x);
  Double_t hit_y[25000];
  TBranch *b_hit_y;
  t1->SetBranchAddress("hit.y",&hit_y, &b_hit_y);
  Double_t hit_z[25000];
  TBranch *b_hit_z;
  t1->SetBranchAddress("hit.z",&hit_z, &b_hit_z);
  Double_t hit_px[25000];
  TBranch *b_hit_px;
  t1->SetBranchAddress("hit.px",&hit_px, &b_hit_px);
  Double_t hit_py[25000];
  TBranch *b_hit_py;
  t1->SetBranchAddress("hit.py",&hit_py, &b_hit_py);
  Double_t hit_pz[25000];
  TBranch *b_hit_pz;
  t1->SetBranchAddress("hit.pz",&hit_pz, &b_hit_pz);
  Double_t hit_vx[25000];
  TBranch *b_hit_vx;
  t1->SetBranchAddress("hit.vx",&hit_vx, &b_hit_vx);
  Double_t hit_vy[25000];
  TBranch *b_hit_vy;
  t1->SetBranchAddress("hit.vy",&hit_vy, &b_hit_vy);
  Double_t hit_vz[25000];
  TBranch *b_hit_vz;
  t1->SetBranchAddress("hit.vz",&hit_vz, &b_hit_vz);
  Double_t hit_vdx[25000];
  TBranch *b_hit_vdx;
  t1->SetBranchAddress("hit.vdx",&hit_vdx, &b_hit_vdx);
  Double_t hit_vdy[25000];
  TBranch *b_hit_vdy;
  t1->SetBranchAddress("hit.vdy",&hit_vdy, &b_hit_vdy);
  Double_t hit_vdz[25000];
  TBranch *b_hit_vdz;
  t1->SetBranchAddress("hit.vdz",&hit_vdz, &b_hit_vdz);
  Double_t hit_p[25000];
  TBranch *b_hit_p;
  t1->SetBranchAddress("hit.p",&hit_p, &b_hit_p);
  Double_t hit_e[25000];
  TBranch *b_hit_e;
  t1->SetBranchAddress("hit.e",&hit_e, &b_hit_e);
  Double_t hit_lambda[25000];
  TBranch *b_hit_lambda;
  t1->SetBranchAddress("hit.lambda",&hit_lambda, &b_hit_lambda);
  Double_t hit_eff[25000];
  TBranch *b_hit_eff;
  t1->SetBranchAddress("hit.eff",&hit_eff, &b_hit_eff);
  Double_t hit_m[25000];
  TBranch *b_hit_m;
  t1->SetBranchAddress("hit.m",&hit_m, &b_hit_m);
  Int_t sci_n;
  TBranch *b_sci_n;
  t1->SetBranchAddress("sci.n",&sci_n, &b_sci_n);
  Int_t sci_det[25000];
  TBranch *b_sci_det;
  t1->SetBranchAddress("sci.det",&sci_det, &b_sci_det);
  Int_t sci_id[25000];
  TBranch *b_sci_id;
  t1->SetBranchAddress("sci.id",&sci_id, &b_sci_id);
  Double_t sci_edep[25000];
  TBranch *b_sci_edep;
  t1->SetBranchAddress("sci.edep",&sci_edep, &b_sci_edep);  

  Int_t nentries = (Int_t)t1->GetEntries();
  
  TH1F *ev_pid_hist = new TH1F("ev_pid_hist", "ev_pid_hist", 20, 0, 20);
  TH1F *ev_pid_hist_thrown = new TH1F("ev_pid_hist_thrown", "ev_pid_hist_thrown", 20, 0, 20);
  TH1F *ev_vx_hist = new TH1F("ev_vx_hist", "ev_vx_hist", 200, -0.1, 0.1);
  TH1F *ev_vy_hist = new TH1F("ev_vy_hist", "ev_vy_hist", 200, -0.01, 0.01);
  TH1F *ev_vz_hist = new TH1F("ev_vz_hist", "ev_vz_hist", 200, -0.01, 0.01);
  TH1F *ev_p_hist = new TH1F("ev_p_hist", "ev_p_hist", 200, 0, 2); 
  TH1F *ev_px_hist = new TH1F("ev_px_hist", "ev_px_hist", 200, -0.5, 1.5);
  TH1F *ev_py_hist = new TH1F("ev_py_hist", "ev_py_hist", 200, -1.0, 1.0);
  TH1F *ev_pz_hist = new TH1F("ev_pz_hist", "ev_pz_hist", 200, -1.0, 1.0);
  TH1F *ev_kine_hist = new TH1F("ev_kine_hist", "ev_kine_hist", 10000, 110, 100000);
  TH1F *hit_n_hist = new TH1F("hit_n_hist", "hit_n_hist", 100, 0, 1000);
  TH1F *hit_pe_hist = new TH1F("hit_pe_hist", "hit_pe_hist", 100, 0, 1000);
  TH1F *hit_det_hist = new TH1F("hit_det_hist", "hit_det_hist", 3, 0, 3);
  TH1F *hit_vid_hist = new TH1F("hit_vid_hist", "hit_vid_hist", 4, -2, 2);
  TH1F *hit_pid_hist = new TH1F("hit_pid_hist", "hit_pid_hist", 40, -10, 30);
  TH1F *hit_trid_hist = new TH1F("hit_trid_hist", "hit_trid_hist", 100, 0, 2500);
  TH1F *hit_x_hist = new TH1F("hit_x_hist", "hit_x_hist", 150, 0, 0.15);
  TH1F *hit_y_hist = new TH1F("hit_y_hist", "hit_y_hist", 600, -0.03, 0.03);
  TH1F *hit_z_hist = new TH1F("hit_z_hist", "hit_z_hist", 600, -0.03, 0.03);
  TH1F *hit_px_hist = new TH1F("hit_px_hist", "hit_px_hist", 700, 0, 0.7);
  TH1F *hit_py_hist = new TH1F("hit_py_hist", "hit_py_hist", 400, -0.2, 0.2);
  TH1F *hit_pz_hist = new TH1F("hit_pz_hist", "hit_pz_hist", 700, -0.1, 0.6);
  TH1F *hit_vx_hist = new TH1F("hit_vx_hist", "hit_vx_hist", 160, 0, 0.16);
  TH1F *hit_vy_hist = new TH1F("hit_vy_hist", "hit_vy_hist", 350, -0.02, 0.15);
  TH1F *hit_vz_hist = new TH1F("hit_vz_hist", "hit_vz_hist", 320, -0.12, 0.2);
  TH1F *hit_vdx_hist = new TH1F("hit_vdx_hist", "hit_vdx_hist", 220, -1.1, 1.1);
  TH1F *hit_vdy_hist = new TH1F("hit_vdy_hist", "hit_vdy_hist", 220, -1.1, 1.1);
  TH1F *hit_vdz_hist = new TH1F("hit_vdz_hist", "hit_vdz_hist", 220, -1.1, 1.1);
  TH1F *hit_p_hist = new TH1F("hit_p_hist", "hit_p_hist", 100, 0, 0.1);
  TH1F *hit_e_hist = new TH1F("hit_e_hist", "hit_e_hist", 100, 0, 0.1);
  TH1F *hit_lambda_hist = new TH1F("hit_lambda_hist", "hit_lambda_hist", 100, 0, 700);
  TH1F *hit_eff_hist = new TH1F("hit_eff_hist", "hit_eff_hist", 100, 0, 1);
  TH1F *hit_m_hist = new TH1F("hit_m_hist", "hit_m_hist", 100, 0, 0.1);
  TH1F *sci_n_hist = new TH1F("sci_n_hist", "sci_n_hist", 2, 0, 2);
  TH1F *sci_det_hist = new TH1F("sci_det_hist", "sci_det_hist", 4, 8, 12);
  TH1F *sci_id_hist = new TH1F("sci_id_hist", "sci_id_hist", 4, -2, 2);
  TH1F *sci_edep_hist = new TH1F("sci_edep_hist", "sci_edep_hist", 100, 0, 0.01);

  TH1F *ev_theta = new TH1F("ev_theta","ev_theta",400,25,65);
  TH1F *ev_theta_thrown = new TH1F("ev_theta_thrown","ev_theta_thrown",400,25,65);  
  TH1F *ev_phi = new TH1F("ev_phi","ev_phi",80,-4,4);
  TH1F *ev_phi_thrown = new TH1F("ev_phi_thrown","ev_phi_thrown",80,-4,4);
  TH1F *ev_kine_hist_thrown = new TH1F("ev_kine_hist_thrown", "ev_kine_hist_thrown", 10000, 110, 100000);

  TH1F *photo_electrons = new TH1F("photo_electrons","photo_electrons",300,0,300);
  TH2F *hit_pe_vs_ev_theta = new TH2F("hit_pe_vs_ev_theta","hit_pe_vs_ev_theta",400,25,65,300,0,300);
  TH2F *ev_vz_vs_ev_theta = new TH2F("ev_vz_vs_ev_theta","ev_vz_vs_ev_theta",400,25,65,22,-0.11,0.11);
  TH2F *hit_pe_vs_ev_kine = new TH2F("hit_pe_vs_ev_kine","hit_pe_vs_ev_kine",110, 0, 100000,300,0,300);

  int num_pe = 0;
  gRandom = new TRandom3();

  for(Int_t i=0; i<nentries; i++){
    t1->GetEntry(i);

    if(ev_pid==13){
      ev_pid_hist_thrown->Fill(ev_pid);
      ev_vx_hist->Fill(ev_vx);
      ev_vy_hist->Fill(ev_vy);
      ev_vz_hist->Fill(ev_vz);
      ev_p_hist->Fill(ev_p);
      ev_px_hist->Fill(ev_px);
      ev_py_hist->Fill(ev_py);
      ev_pz_hist->Fill(ev_pz);
      hit_pe_hist->Fill(hit_pe);
      sci_n_hist->Fill(sci_n);

      ev_theta_thrown->Fill(acos(ev_pz/ev_p)*(180/PI)-45);
      ev_phi_thrown->Fill(atan(ev_py/ev_px)*(180/PI));
      ev_kine_hist_thrown->Fill(ev_kine-110);

      if(sci_n==3){
        for(Int_t sci_idx=0; sci_idx<sci_n; sci_idx++){
           if(sci_det[sci_idx]==10){
      	     ev_pid_hist->Fill(ev_pid);
             ev_kine_hist->Fill(ev_kine-110);
             ev_theta->Fill(acos(ev_pz/ev_p)*(180/PI)-45);
	     ev_phi->Fill(atan(ev_py/ev_px)*(180/PI));
             hit_pe_vs_ev_theta->Fill(acos(ev_pz/ev_p)*(180/PI)-45,hit_pe);
	     ev_vz_vs_ev_theta->Fill(acos(ev_pz/ev_p)*(180/PI)-45,ev_vz);
	     hit_pe_vs_ev_kine->Fill(ev_kine-110,hit_pe);
             for(Int_t hit_idx=0; hit_idx<hit_n; hit_idx++){
                //if(hit_vx[hit_idx] > -0.05 && hit_vx[hit_idx] < 0.041){
                  //if(hit_vy[hit_idx] > -0.016 && hit_vy[hit_idx] < 0.016){
                    //if(hit_vz[hit_idx] > -0.049 && hit_vz[hit_idx] < 0.046){ 
                      if(gRandom->Rndm() <= hit_eff[hit_idx]){
		        if(hit_pid[hit_idx] == 0){
                          num_pe++;                    
		        }
	              }
                    //}
                  //}
                //}
             }
             hit_n_hist->Fill(hit_n);
    	     photo_electrons->Fill(num_pe);
             num_pe = 0;
           }          
        }
      }

      for(Int_t hit_idx=0; hit_idx<hit_n; hit_idx++){
         hit_det_hist->Fill(hit_det[hit_idx]);
         hit_vid_hist->Fill(hit_vid[hit_idx]);
         hit_pid_hist->Fill(hit_pid[hit_idx]);
         hit_trid_hist->Fill(hit_trid[hit_idx]);
         hit_x_hist->Fill(hit_x[hit_idx]);
         hit_y_hist->Fill(hit_y[hit_idx]);
         hit_z_hist->Fill(hit_z[hit_idx]);
         hit_px_hist->Fill(hit_px[hit_idx]);
         hit_py_hist->Fill(hit_py[hit_idx]);
         hit_pz_hist->Fill(hit_pz[hit_idx]);
         hit_vx_hist->Fill(hit_vx[hit_idx]);
         hit_vy_hist->Fill(hit_vy[hit_idx]);
         hit_vz_hist->Fill(hit_vz[hit_idx]);
         hit_vdx_hist->Fill(hit_vdx[hit_idx]);
         hit_vdy_hist->Fill(hit_vdy[hit_idx]);
         hit_vdz_hist->Fill(hit_vdz[hit_idx]);
         hit_p_hist->Fill(hit_p[hit_idx]);
         hit_e_hist->Fill(hit_e[hit_idx]);
         hit_lambda_hist->Fill(hit_lambda[hit_idx]);
         hit_eff_hist->Fill(hit_eff[hit_idx]);
         hit_m_hist->Fill(hit_m[hit_idx]);
         sci_det_hist->Fill(sci_det[hit_idx]);
         sci_id_hist->Fill(sci_id[hit_idx]);
         sci_edep_hist->Fill(sci_edep[hit_idx]);      
      }
    }
  }

  Hlist.Add(ev_pid_hist);
  Hlist.Add(ev_pid_hist_thrown);
  Hlist.Add(ev_vx_hist);
  Hlist.Add(ev_vy_hist);
  Hlist.Add(ev_vz_hist);
  Hlist.Add(ev_p_hist);
  Hlist.Add(ev_px_hist);
  Hlist.Add(ev_py_hist);
  Hlist.Add(ev_pz_hist);
  Hlist.Add(ev_theta);
  Hlist.Add(ev_phi);

  Hlist.Add(ev_theta_thrown);
  Hlist.Add(ev_phi_thrown);

  Hlist.Add(ev_kine_hist);

  Hlist.Add(ev_kine_hist_thrown);

  Hlist.Add(hit_n_hist);
  Hlist.Add(hit_pe_hist);
  Hlist.Add(hit_det_hist);
  Hlist.Add(hit_vid_hist);
  Hlist.Add(hit_pid_hist);
  Hlist.Add(hit_trid_hist);
  Hlist.Add(hit_x_hist);
  Hlist.Add(hit_y_hist);
  Hlist.Add(hit_z_hist);
  Hlist.Add(hit_px_hist);
  Hlist.Add(hit_py_hist);
  Hlist.Add(hit_pz_hist);
  Hlist.Add(hit_vx_hist);
  Hlist.Add(hit_vy_hist);
  Hlist.Add(hit_vz_hist); 
  Hlist.Add(hit_vdx_hist);
  Hlist.Add(hit_vdy_hist);
  Hlist.Add(hit_vdz_hist);
  Hlist.Add(hit_p_hist);
  Hlist.Add(hit_e_hist);
  Hlist.Add(hit_lambda_hist);
  Hlist.Add(hit_m_hist);
  Hlist.Add(sci_det_hist);
  Hlist.Add(sci_id_hist);
  Hlist.Add(sci_edep_hist);
  
  Hlist.Add(photo_electrons);  
  Hlist.Add(hit_pe_vs_ev_theta);  
  Hlist.Add(ev_vz_vs_ev_theta);
  Hlist.Add(hit_pe_vs_ev_kine);

  TFile fout("out.root","recreate"); 
  Hlist.Write();
 
}

PlotHist(){

gROOT->SetStyle("Plain");
gStyle->SetFillColor(10);
gStyle->SetFrameBorderSize(0);
gStyle->SetStatStyle(0);
gStyle->SetTitleStyle(0);
gStyle->SetLegendBorderSize(0); 
gROOT->ForceStyle();

char filename[356];
sprintf(filename,"/home/bulacarl/solid/data/qsimA_thickness_5mm_separation_5mm_events_2,5E6_NoMirrors_thetaMin_79,7deg_thetaMax_100,3deg_phiMin_-3,6deg_phiMax_3,6deg_CryMuons_emin_110MeV_emax_100GeV_Source_xmin_-56cm_xmax_-56cm_ymin_-1,75cm_ymax_1,75cm_zmin_-10cm_zmax_10cm_QER7723Q.out");
readfile(filename);
TFile *f1 = new TFile("out.root");

TCanvas * c1 = new TCanvas("c1", "c1", 600, 500);

char histname1[256] = "photo_electrons";

TH1F *photo_electrons = (TH1F*)f1->Get(histname1);
photo_electrons->SetLineColor(kBlack);
photo_electrons->SetTitle("Photo-Electron Distribution");
photo_electrons->GetXaxis()->SetTitle("Photo-electrons");
photo_electrons->GetYaxis()->SetTitle("Events");
photo_electrons->Draw();

double Mean = photo_electrons->GetMean();
double RMS = photo_electrons->GetRMS();

char ratio[256];
sprintf(ratio,"Res. = %g\n",RMS/Mean);
TLatex* text = new TLatex();
text->SetTextColor(kBlack);
text->SetTextSize(0.05);
text->DrawLatex(0.6,7.0,ratio);

TCanvas * c2 = new TCanvas("c2", "c2", 600, 500);

char histname2[256] = "hit_n_hist";

TH1F *hit_n_hist = (TH1F*)f1->Get(histname2);
hit_n_hist->SetLineColor(kBlack);
hit_n_hist->SetTitle("Photon Distribution");
hit_n_hist->GetXaxis()->SetTitle("Photons");
hit_n_hist->GetYaxis()->SetTitle("Events");
hit_n_hist->Draw();

double Mean = hit_n_hist->GetMean();
double RMS = hit_n_hist->GetRMS();

char ratio[256];
sprintf(ratio,"Res. = %g\n",RMS/Mean);
TLatex* text = new TLatex();
text->SetTextColor(kBlack);
text->SetTextSize(0.05);
text->DrawLatex(0.6,7.0,ratio);

TCanvas * c3 = new TCanvas("c3", "c3", 600, 500);

char histname3_1[256] = "ev_kine_hist_thrown";

TH1F *ev_kine_hist_thrown = (TH1F*)f1->Get(histname3_1);
ev_kine_hist_thrown->SetLineColor(kBlack);
ev_kine_hist_thrown->SetTitle("Beam Energy");
ev_kine_hist_thrown->GetXaxis()->SetTitle("Energy[MeV]");
ev_kine_hist_thrown->GetYaxis()->SetTitle("Events");
c3->SetLogx();
c3->SetLogy();
ev_kine_hist_thrown->Draw();

c3->Modified();
c3->Update();
TPaveStats *stats1 = (TPaveStats*)c3->GetPrimitive("stats");
stats1->SetName("stats1");
stats1->SetTextColor(kBlack); 
stats1->SetX1NDC(0.12); stats1->SetX2NDC(0.32); stats1->SetY1NDC(0.75);
c3->Update();

char histname3_2[256] = "ev_kine_hist";

TH1F *ev_kine_hist = (TH1F*)f1->Get(histname3_2);
ev_kine_hist->SetLineColor(kRed);
ev_kine_hist->Draw("sames");

c3->Modified();
c3->Update();
TPaveStats *stats2 = (TPaveStats*)c3->GetPrimitive("stats");
stats2->SetName("stats2");
stats2->SetTextColor(kRed); 
stats2->SetX1NDC(0.12); stats2->SetX2NDC(0.32); stats2->SetY1NDC(0.75);
c3->Update();

TCanvas * c4 = new TCanvas("c4", "c4", 600, 500);

char histname4_1[256] = "ev_theta_thrown";

TH1F *ev_theta_thrown = (TH1F*)f1->Get(histname4_1);
ev_theta_thrown->SetLineColor(kBlack);
ev_theta_thrown->SetTitle("Polar Angle");
ev_theta_thrown->GetXaxis()->SetTitle("#theta[deg]");
ev_theta_thrown->GetYaxis()->SetTitle("Events");
ev_theta_thrown->Draw();

c4->Modified();
c4->Update();
TPaveStats *stats1 = (TPaveStats*)c4->GetPrimitive("stats");
stats1->SetName("stats1");
stats1->SetTextColor(kBlack); 
stats1->SetX1NDC(0.12); stats1->SetX2NDC(0.32); stats1->SetY1NDC(0.75);
c4->Update();

char histname4_2[256] = "ev_theta";

TH1F *ev_theta = (TH1F*)f1->Get(histname4_2);
ev_theta->SetLineColor(kRed);
ev_theta->Draw("sames");

c4->Modified();
c4->Update();
TPaveStats *stats2 = (TPaveStats*)c4->GetPrimitive("stats");
stats2->SetName("stats2");
stats2->SetTextColor(kRed); 
stats2->SetX1NDC(0.12); stats2->SetX2NDC(0.32); stats2->SetY1NDC(0.75);
c4->Update();

TCanvas * c5 = new TCanvas("c5", "c5", 600, 500);

char histname5_1[256] = "ev_phi_thrown";

TH1F *ev_phi_thrown = (TH1F*)f1->Get(histname5_1);
ev_phi_thrown->SetLineColor(kBlack);
ev_phi_thrown->SetTitle("Azimuthal Angle");
ev_phi_thrown->GetXaxis()->SetTitle("#phi[deg]");
ev_phi_thrown->GetYaxis()->SetTitle("Events");
ev_phi_thrown->Draw();

c5->Modified();
c5->Update();
TPaveStats *stats1 = (TPaveStats*)c5->GetPrimitive("stats");
stats1->SetName("stats1");
stats1->SetTextColor(kBlack); 
stats1->SetX1NDC(0.12); stats1->SetX2NDC(0.32); stats1->SetY1NDC(0.75);
c5->Update();

char histname5_2[256] = "ev_phi";

TH1F *ev_phi = (TH1F*)f1->Get(histname5_2);
ev_phi->SetLineColor(kRed);
ev_phi->Draw("sames");

c5->Modified();
c5->Update();
TPaveStats *stats2 = (TPaveStats*)c5->GetPrimitive("stats");
stats2->SetName("stats2");
stats2->SetTextColor(kRed); 
stats2->SetX1NDC(0.12); stats2->SetX2NDC(0.32); stats2->SetY1NDC(0.75);
c5->Update();

TCanvas * c6 = new TCanvas("c6", "c6", 600, 500);

char histname6[256] = "hit_pe_vs_ev_theta";

TH2F *hit_pe_vs_ev_theta = (TH2F*)f1->Get(histname6);
hit_pe_vs_ev_theta->SetLineColor(kBlack);
hit_pe_vs_ev_theta->SetTitle("Photo Electrons vs Polar Angle");
hit_pe_vs_ev_theta->GetXaxis()->SetTitle("#theta[deg]");
hit_pe_vs_ev_theta->GetYaxis()->SetTitle("Photo Electrons");
hit_pe_vs_ev_theta->Draw("CONTZ");

TCanvas * c7 = new TCanvas("c7", "c7", 600, 500);

char histname7[256] = "ev_vz_vs_ev_theta";

TH2F *ev_vz_vs_ev_theta = (TH2F*)f1->Get(histname7);
ev_vz_vs_ev_theta->SetLineColor(kBlack);
ev_vz_vs_ev_theta->SetTitle("ev.vz vs Polar Angle");
ev_vz_vs_ev_theta->GetXaxis()->SetTitle("#theta[deg]");
ev_vz_vs_ev_theta->GetYaxis()->SetTitle("vertex z-axis");
ev_vz_vs_ev_theta->Draw("CONTZ");

TCanvas * c8 = new TCanvas("c8", "c8", 600, 500);

char histname8[256] = "hit_lambda_hist";

TH1F *hit_lambda_hist = (TH1F*)f1->Get(histname8);
hit_lambda_hist->SetLineColor(kBlack);
hit_lambda_hist->SetTitle("Photon Wavelength");
hit_lambda_hist->GetXaxis()->SetTitle("#lambda[nm]");
hit_lambda_hist->GetYaxis()->SetTitle("Events");
hit_lambda_hist->Draw();

TCanvas * c9 = new TCanvas("c9", "c9", 600, 500);

char histname9_1[256] = "ev_pid_hist_thrown";

TH1F *ev_pid_hist_thrown = (TH1F*)f1->Get(histname9_1);
ev_pid_hist_thrown->SetLineColor(kBlack);
ev_pid_hist_thrown->SetTitle("ev.pid");
ev_pid_hist_thrown->GetXaxis()->SetTitle("Event Particle ID");
ev_pid_hist_thrown->GetYaxis()->SetTitle("Events");
ev_pid_hist_thrown->Draw();

c9->Modified();
c9->Update();
TPaveStats *stats1 = (TPaveStats*)c9->GetPrimitive("stats");
stats1->SetName("stats1");
stats1->SetTextColor(kBlack); 
stats1->SetX1NDC(0.12); stats1->SetX2NDC(0.32); stats1->SetY1NDC(0.75);
c9->Update();

char histname9_2[256] = "ev_pid_hist";

TH1F *ev_pid_hist = (TH1F*)f1->Get(histname9_2);
ev_pid_hist->SetLineColor(kRed);
ev_pid_hist->Draw("sames");

c9->Modified();
c9->Update();
TPaveStats *stats2 = (TPaveStats*)c9->GetPrimitive("stats");
stats2->SetName("stats2");
stats2->SetTextColor(kRed); 
stats2->SetX1NDC(0.12); stats2->SetX2NDC(0.32); stats2->SetY1NDC(0.75);
c9->Update();

TCanvas * c10 = new TCanvas("c10", "c10", 600, 500);
c10->SetLogx();

char histname10[256] = "hit_pe_vs_ev_kine";

TH2F *hit_pe_vs_ev_kine = (TH2F*)f1->Get(histname10);
hit_pe_vs_ev_kine->SetLineColor(kBlack);
hit_pe_vs_ev_kine->SetTitle("Photo-electrons vs Muon Energy");
hit_pe_vs_ev_kine->GetXaxis()->SetTitle("#E[MeV]");
hit_pe_vs_ev_kine->GetYaxis()->SetTitle("Events");
hit_pe_vs_ev_kine->Draw("CONTZ");

TImage *img1 = TImage::Create();
//img1->FromPad(c, 10, 10, 300, 200);
img1->FromPad(c1);
img1->WriteImage("/home/bulacarl/solid/data/plots/hit_pe.png");

TImage *img2 = TImage::Create();
//img2->FromPad(c, 10, 10, 300, 200);
img2->FromPad(c2);
img2->WriteImage("/home/bulacarl/solid/data/plots/hit_n.png");

TImage *img3 = TImage::Create();
//img3->FromPad(c, 10, 10, 300, 200);
img3->FromPad(c3);
img3->WriteImage("/home/bulacarl/solid/data/plots/ev_kine.png");

TImage *img4 = TImage::Create();
//img4->FromPad(c, 10, 10, 300, 200);
img4->FromPad(c4);
img4->WriteImage("/home/bulacarl/solid/data/plots/ev_theta.png");

TImage *img5 = TImage::Create();
//img5->FromPad(c, 10, 10, 300, 200);
img5->FromPad(c5);
img5->WriteImage("/home/bulacarl/solid/data/plots/ev_phi.png");

TImage *img6 = TImage::Create();
//img5->FromPad(c, 10, 10, 300, 200);
img6->FromPad(c6);
img6->WriteImage("/home/bulacarl/solid/data/plots/hit_pe_vs_ev_theta.png");

TImage *img7 = TImage::Create();
//img5->FromPad(c, 10, 10, 300, 200);
img7->FromPad(c7);
img7->WriteImage("/home/bulacarl/solid/data/plots/ev_vz_vs_ev_theta.png");

TImage *img8 = TImage::Create();
//img5->FromPad(c, 10, 10, 300, 200);
img8->FromPad(c8);
img8->WriteImage("/home/bulacarl/solid/data/plots/hit_lambda.png");

TImage *img9 = TImage::Create();
//img5->FromPad(c, 10, 10, 300, 200);
img9->FromPad(c9);
img9->WriteImage("/home/bulacarl/solid/data/plots/ev_pid.png");

TImage *img10 = TImage::Create();
//img5->FromPad(c, 10, 10, 300, 200);
img10->FromPad(c10);
img10->WriteImage("/home/bulacarl/solid/data/plots/hit_pe_vs_ev_kine.png");

}
