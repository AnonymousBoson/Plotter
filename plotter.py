#!/usr/bin/env python
#// Small dumb code to play with trees
#// O.Bondu, F. Bojarski (May 2014)
# Various python imports
from os import path
from math import log10, pow
import collections
# ROOT setup
import ROOT
from ROOT import TFile, TTree, TLine, TChain, TCanvas, TH1D, TLatex, TLegend, TLorentzVector
ROOT.gROOT.Reset()
ROOT.gROOT.SetBatch()
ROOT.gROOT.ProcessLine(".x setTDRStyle.C")
ROOT.TGaxis.SetMaxDigits(3);

c1 = TCanvas()
#afs_plottree = "/afs/cern.ch/work/o/obondu/public/forRadion/plotTrees/v22/2014-12-16_selection_withRegression_noMassCut_v22"
afs_plottree = "/afs/cern.ch/work/o/obondu/public/forRadion/plotTrees/v22/2014-12-16_selection_noRegression_noMassCut_v22"
eos_tree = "root://eoscms//eos/cms/store/cmst3/user/obondu/H2GGLOBE/Radion/trees/radion_redu_11_tree_08"

#regression = "withRegression"
regression = "noRegression"

intL = 19712.
samples = []
# samples.append([ name, typ, dirpath, subdir, file, tree, sample_cut, color, style, label , sigma , N])
#samples.append(["Radion_m300", -300, afs_plottree, "", "Radion_m300_8TeV_" + regression + "_noMassCut_v*.root", "Radion_m300_8TeV", "evweight_w_btagSF", ROOT.kBlue-2, 0, "m_{X} = 300 GeV" , 13.55e-3, 39971])
#samples.append(["Radion_m500", -50, afs_plottree, "", "Radion_m500_8TeV_" + regression + "_noMassCut_v*.root", "Radion_m500_8TeV", "evweight_w_btagSF", ROOT.kMagenta+2, 0, "m_{X} = 500 GeV" , 13.55e-3, 39969])
#samples.append(["Data", 0, afs_plottree, "", "Data_" + regression + "_noMassCut_v*.root", "Data", "(gg_mass < 120 || gg_mass > 130) * (njets_kRadionID_and_CSVM >= 0)", ROOT.kBlack, 0, "Data (m_{#gamma#gamma}-blind)", 1., 1001822])
#samples.append(["Data", 0, afs_plottree, "", "Data_" + regression + "_noMassCut_v*.root", "Data", "njets_kRadionID_and_CSVM >= 0", ROOT.kBlack, 0, "Data (unblind)", 1., 1001822])
#samples.append(["ControlSample", 1, afs_plottree, "", "Data_" + regression + "_noMassCut_controlSampleWeighted_v*.root", "Data", "evweight_w_btagSF", ROOT.kRed, 3003, "CS w", 1., 1001822])
#samples.append(["ControlSampleUNW", -1, afs_plottree, "", "Data_" + regression + "_noMassCut_controlSample_v*.root", "Data", "", ROOT.kBlue, 1, "CS unw", 1., 1001822])
samples.append(["ggHH_8TeV", 70, afs_plottree, "", "ggHH_8TeV_" + regression + "_noMassCut_v*.root", "ggHH_8TeV", "evweight_w_btagSF / 0.0000212", ROOT.kGreen+2, 0, "ggHH" , 13.55e-3, 96880])
#samples.append(["ggHH_8TeV", 70, afs_plottree, "", "ggHH_8TeV_" + regression + "_noMassCut_v*.root", "ggHH_8TeV", "evweight_w_btagSF * (njets_kRadionID_and_CSVM >= 0)", ROOT.kRed+2, 1001, "SM Higgs" , 1., 14404429])
#samples.append(["bbh_m125_8TeV", 70, afs_plottree, "", "bbh_m125_8TeV_" + regression + "_noMassCut_v*.root", "bbh_m125_8TeV", "evweight_w_btagSF * (njets_kRadionID_and_CSVM >= 0)", ROOT.kRed+2, 1001, "SM Higgs" , 1., 99434])
samples.append(["bbh_m125_8TeV", -70, afs_plottree, "", "bbh_m125_8TeV_" + regression + "_noMassCut_v*.root", "bbh_m125_8TeV", "evweight_w_btagSF * (njets_kRadionID_and_CSVM >= 0)", ROOT.kRed+2, 3002, "bbH" , 1., 99434])
#samples.append(["tth_m125_8TeV", 70, afs_plottree, "", "tth_m125_8TeV_" + regression + "_noMassCut_v*.root", "tth_m125_8TeV", "evweight_w_btagSF * (njets_kRadionID_and_CSVM >= 0)", ROOT.kRed+2, 1001, "SM Higgs" , 1., 93183])
#samples.append(["wzh_m125_8TeV_zh", 70, afs_plottree, "", "wzh_m125_8TeV_zh_" + regression + "_noMassCut_v*.root", "wzh_m125_8TeV_zh", "evweight_w_btagSF * (njets_kRadionID_and_CSVM >= 0)", ROOT.kRed+2, 1001, "SM Higgs" , 1., 100151])
#samples.append(["wzh_m125_8TeV_wh", 70, afs_plottree, "", "wzh_m125_8TeV_wh_" + regression + "_noMassCut_v*.root", "wzh_m125_8TeV_wh", "evweight_w_btagSF * (njets_kRadionID_and_CSVM >= 0)", ROOT.kRed+2, 1001, "SM Higgs" , 1., 100151])
#samples.append(["vbf_m125_8TeV", 70, afs_plottree, "", "vbf_m125_8TeV_" + regression + "_noMassCut_v*.root", "vbf_m125_8TeV", "evweight_w_btagSF * (njets_kRadionID_and_CSVM >= 0)", ROOT.kRed+2, 1001, "SM Higgs" , 1., 99671])
#samples.append(["ggh_m125_powheg_8TeV", 70, afs_plottree, "", "ggh_m125_powheg_8TeV_" + regression + "_noMassCut_v*.root", "ggh_m125_powheg_8TeV", "evweight_w_btagSF * (njets_kRadionID_and_CSVM >= 0)", ROOT.kRed+2, 1001, "SM Higgs" , 1., 99870])
#samples.append(["ZGToLLG_8TeV", 60, afs_plottree, "", "ZGToLLG_8TeV_" + regression + "_noMassCut_v*.root", "ZGToLLG_8TeV", "evweight_w_btagSF * (njets_kRadionID_and_CSVM >= 0)", ROOT.kCyan+2, 1001, "W/Z + #gamma/#gamma#gamma" , 1., 14404429])
#samples.append(["LNuGG_ISR_8TeV", 60, afs_plottree, "", "LNuGG_ISR_8TeV_" + regression + "_noMassCut_v*.root", "LNuGG_ISR_8TeV", "evweight_w_btagSF * (njets_kRadionID_and_CSVM >= 0)", ROOT.kCyan+2, 1001, "W/Z + #gamma/#gamma#gamma" , 1., 14404429])
#samples.append(["LNuGG_FSR_8TeV", 60, afs_plottree, "", "LNuGG_FSR_8TeV_" + regression + "_noMassCut_v*.root", "LNuGG_FSR_8TeV", "evweight_w_btagSF * (njets_kRadionID_and_CSVM >= 0)", ROOT.kCyan+2, 1001, "W/Z + #gamma/#gamma#gamma" , 1., 14404429])
#samples.append(["TTGJets_8TeV", 50, afs_plottree, "", "TTGJets_8TeV_" + regression + "_noMassCut_v*.root", "TTGJets_8TeV", "evweight_w_btagSF * (njets_kRadionID_and_CSVM >= 0)", ROOT.kYellow+2, 1001, "t/t#bar{t} + #gamma/#gamma#gamma" , 1., 14404429])
#samples.append(["tGG_8TeV", 50, afs_plottree, "", "tGG_8TeV_" + regression + "_noMassCut_v*.root", "tGG_8TeV", "evweight_w_btagSF * (njets_kRadionID_and_CSVM >= 0)", ROOT.kYellow+2, 1001, "t/t#bar{t} + #gamma/#gamma#gamma" , 1., 14404429])
#samples.append(["ttGG_8TeV", 50, afs_plottree, "", "ttGG_8TeV_" + regression + "_noMassCut_v*.root", "ttGG_8TeV", "evweight_w_btagSF * (njets_kRadionID_and_CSVM >= 0)", ROOT.kYellow+2, 1001, "t/t#bar{t} + #gamma/#gamma#gamma" , 1., 14404429])
#samples.append(["DYJetsToLL", 40, afs_plottree, "", "DYJetsToLL_" + regression + "_noMassCut_v*.root", "DYJetsToLL", "evweight_w_btagSF * (njets_kRadionID_and_CSVM >= 0)", ROOT.kMagenta+2, 1001, "DY" , 1., 14404429])
#samples.append(["qcd_40_8TeV_ff", 30, afs_plottree, "", "qcd_40_8TeV_ff_" + regression + "_noMassCut_v*.root", "qcd_40_8TeV_ff", "(evweight_w_btagSF) * (njets_kRadionID_and_CSVM >= 0)", ROOT.kBlue+3, 1001, "QCD j" , 1., 14404429])
#samples.append(["qcd_30_8TeV_ff", 30, afs_plottree, "", "qcd_30_8TeV_ff_" + regression + "_noMassCut_v*.root", "qcd_30_8TeV_ff", "(evweight_w_btagSF) * (njets_kRadionID_and_CSVM >= 0)", ROOT.kBlue+3, 1001, "QCD j" , 1., 14404429])
#samples.append(["qcd_30_8TeV_pf", 20, afs_plottree, "", "qcd_30_8TeV_pf_" + regression + "_noMassCut_v*.root", "qcd_30_8TeV_pf", "(evweight_w_btagSF) * (njets_kRadionID_and_CSVM >= 0)", ROOT.kBlue-4, 1001, "QCD #gamma + j" , 1., 6047441])
#samples.append(["qcd_40_8TeV_pf", 20, afs_plottree, "", "qcd_40_8TeV_pf_" + regression + "_noMassCut_v*.root", "qcd_40_8TeV_pf", "(evweight_w_btagSF) * (njets_kRadionID_and_CSVM >= 0)", ROOT.kBlue-4, 1001, "QCD #gamma + j" , 1., 9764546])
#samples.append(["gjet_20_8TeV_pf", 20, afs_plottree, "", "gjet_20_8TeV_pf_" + regression + "_noMassCut_v*.root", "gjet_20_8TeV_pf", "evweight_w_btagSF * (njets_kRadionID_and_CSVM >= 0)", ROOT.kBlue-4, 1001, "QCD #gamma + j" , 1., 5901106])
#samples.append(["gjet_40_8TeV_pf", 20, afs_plottree, "", "gjet_40_8TeV_pf_" + regression + "_noMassCut_v*.root", "gjet_40_8TeV_pf", "evweight_w_btagSF * (njets_kRadionID_and_CSVM >= 0)", ROOT.kBlue-4, 1001, "QCD #gamma + j" , 1., 17722752])
#samples.append(["diphojet_sherpa_8TeV", 10, afs_plottree, "", "diphojet_sherpa_8TeV_" + regression + "_noMassCut_v*.root", "diphojet_sherpa_8TeV", "evweight_w_btagSF * (njets_kRadionID_and_CSVM >= 0)", ROOT.kGreen+2, 1001, "QCD #gamma#gamma + j" , 1., 14404429])
#samples.append(["ggHH_Lam_0d0_Yt_1d0_c2_0d0_8TeV", -500010000, afs_plottree, "", "ggHH_Lam_0d0_Yt_1d0_c2_0d0_8TeV_" + regression + "_noMassCut_v*.root", "ggHH_Lam_0d0_Yt_1d0_c2_0d0_8TeV", "evweight_w_btagSF", ROOT.kRed, 0, "(#lambda, y_{t}, c_{2}) = (0, 1, 0)" , 13.55e-3, 19600])

#samples.append(["ggHH_Lam_1d0_Yt_1d0_c2_0d0_8TeV", -501010000, afs_plottree, "", "ggHH_Lam_1d0_Yt_1d0_c2_0d0_8TeV_" + regression + "_noMassCut_v*.root", "ggHH_Lam_1d0_Yt_1d0_c2_0d0_8TeV", "evweight_w_btagSF", ROOT.kBlue, 0, "(#lambda, y_{t}, c_{2}) = (1, 1, 0)" , 13.55e-3, 20000])
#samples.append(["ggHH_Lam_1d0_Yt_1d0_c2_0d0_8TeV", -501010000, "", "", "ggHH_Lam_1d0_Yt_1d0_c2_0d0_8TeV_" + regression + "_noMassCut_v*.root", "ggHH_Lam_1d0_Yt_1d0_c2_0d0_8TeV", "evweight_w_btagSF", ROOT.kBlue, 0, "(#lambda, y_{t}, c_{2}) = (1, 1, 0)" , 13.55e-3, 20000])
#samples.append(["ggHH_8TeV", 500000000, afs_plottree, "", "ggHH_8TeV_" + regression + "_noMassCut_v*.root", "ggHH_8TeV", "evweight_w_btagSF", ROOT.kRed, 0, "SM" , 13.55e-3, 96880])


#####plots.append([ name2, variable, plot_cut, norm, binning, title, additional_info, cutline, cutline2 ])
plots = []
#plots.append(["pho1_pt", "pho1_pt", "", 1, "(50, 0, 400)", "p_{T}^{#gamma1} (GeV)", "", "", ""])
#plots.append(["pho2_pt", "pho2_pt", "", 1, "(50, 0, 400)", "p_{T}^{#gamma2} (GeV)", "", "", ""])
plots.append(["jet1_pt_norm1", "jet1_pt", "", 1, "(100, 0, 500)", "p_{T}^{jet1} (GeV)", "", 25., ""])
plots.append(["jet2_pt_norm1", "jet2_pt", "", 1, "(100, 0, 500)", "p_{T}^{jet2} (GeV)", "", 25., ""])
#plots.append(["pho1_eta", "pho1_eta", "", 1, "(30, -3., 3.)", "eta^{#gamma1}", "", "", ""])
#plots.append(["pho2_eta", "pho2_eta", "", 1, "(30, -3., 3.)", "eta^{#gamma2}", "", "", ""])
#plots.append(["jet1_eta", "jet1_eta", "", intL, "(100, -5, 5)", "eta^{jet1}", "", "", ""])
#plots.append(["jet2_eta", "jet2_eta", "", intL, "(100, -5, 5)", "eta^{jet1}", "", "", ""])
#plots.append(["pho1_phi", "pho1_phi", "", intL, "(63, -3.15, 3.15)", "phi^{#gamma1}", "", "", ""])
#plots.append(["pho2_phi", "pho2_phi", "", intL, "(63, -3.15, 3.15)", "phi^{#gamma2}", "", "", ""])
#plots.append(["jet1_phi", "jet1_phi", "", intL, "(100, -5, 5)", "phi^{jet1}", "", "", ""])
#plots.append(["jet2_phi", "jet2_phi", "", intL, "(100, -5, 5)", "phi^{jet2}", "", "", ""])
#plots.append(["jj_phi", "jj_phi", "", intL, "(100, -5, 5)", "phi^{jj}", "", "", ""])
#plots.append(["jj_eta", "jj_eta", "", intL, "(100, -5, 5)", "eta^{jj}", "", "", ""])
#plots.append(["gg_phi", "gg_phi", "", intL, "(63, -3.15, 3.15)", "phi^{#gamma#gamma}", "", "", ""])
#plots.append(["gg_eta", "gg_eta", "", intL, "(63, -3.15, 3.15)", "eta^{#gamma#gamma}", "", "", ""])
#plots.append(["jj_pt", "jj_pt", "", intL, "(500, 0, 500)", "p_{T}^{jj} (GeV)", "", "", ""])
#plots.append(["gg_pt", "gg_pt", "", intL, "(500, 0, 500)", "p_{T}^{#gamma#gamma} (GeV)", "", "", ""])
#plots.append(["pho1_mass", "pho1_mass", "", intL, "(100, -1, 1)", "mass^{#gamma1} (GeV)", "", "", ""])
#plots.append(["pho2_mass", "pho2_mass", "", intL, "(100, -1, 1)", "mass^{#gamma2} (GeV)", "", "", ""])
#plots.append(["jet1_mass", "jet1_mass", "", intL, "(100, 0, 100)", "mass^{jet1} (GeV)", "", "", ""])
#plots.append(["jet2_mass", "jet2_mass", "", intL, "(100, 0, 100)", "mass^{jet2} (GeV)", "", "", ""])
#plots.append(["jj_mass_normData", "jj_mass", "", "data", "(50, 0, 500)", "mass^{jj} (GeV)", "", "", ""])
#plots.append(["gg_mass_normData", "gg_mass", "", "data", "(40, 100, 180)", "mass^{#gamma#gamma} (GeV)", "", "", ""])
plots.append(["jj_mass_norm1", "jj_mass", "", 1, "(50, 0, 500)", "mass^{jj} (GeV)", "", "", ""])
#plots.append(["gg_mass_norm1", "gg_mass", "", 1, "(40, 100, 180)", "mass^{#gamma#gamma} (GeV)", "", "", ""])
#plots.append(["gr_hgg_p4_mass_norm1", "gr_hgg_p4_mass", "", 1, "(40, 100, 180)", "mass^{#gamma#gamma}_{GEN} (GeV)", "", "", ""])
#plots.append(["gr_hbb_p4_mass_norm1", "gr_hbb_p4_mass", "", 1, "(40, 100, 180)", "mass^{bb}_{GEN} (GeV)", "", "", ""])
#plots.append(["gr_hjj_p4_mass_norm1", "gr_hjj_p4_mass", "", 1, "(50, 50, 200)", "mass^{jj}_{GEN} (GeV)", "", "", ""])
#plots.append(["gr_radion_p4_mass_norm1", "gr_radion_p4_mass", "", 1, "(60, 200, 800)", "mass^{#gamma#gamma jj}_{GEN} (GeV)", "", "", ""])
#plots.append(["gr_hgg_p4_pt_norm1", "gr_hgg_p4_pt", "", 1, "(50, 0, 500)", "pt^{#gamma#gamma}_{GEN} (GeV)", "", "", ""])
#plots.append(["gr_hbb_p4_pt_norm1", "gr_hbb_p4_pt", "", 1, "(50, 0, 500)", "pt^{bb}_{GEN} (GeV)", "", "", ""])
#plots.append(["gr_hjj_p4_pt_norm1", "gr_hjj_p4_pt", "", 1, "(50, 0, 500)", "pt^{jj}_{GEN} (GeV)", "", "", ""])
#plots.append(["gr_radion_p4_pt_norm1", "gr_radion_p4_pt", "", 1, "(50, 0, 500)", "pt^{#gamma#gamma jj}_{GEN} (GeV)", "", "", ""])
#plots.append(["gr_dEta_gg_jj_norm1", "gr_dEta_gg_jj", "", 1, "(50, -5, 5)", "#Delta #eta (#gamma#gamma, jj)_{GEN}", "", "", ""])
#plots.append(["gr_dPhi_gg_jj_norm1", "gr_dPhi_gg_jj", "", 1, "(63, -3.15, 3.15)", "#Delta #phi (#gamma#gamma, jj)_{GEN}", "", "", ""])
#plots.append(["gr_dR_gg_jj_norm1", "gr_dR_gg_jj", "", 1, "(40, 0, 6)", "#Delta R (#gamma#gamma, jj)_{GEN}", "", "", ""])
#plots.append(["gr_g1_p4_pt_norm1", "gr_g1_p4_pt", "", 1, "(50, 0, 400)", "p_{T}^{#gamma 1}_{GEN} (GeV)", "", "", ""])
#plots.append(["gr_g2_p4_pt_norm1", "gr_g2_p4_pt", "", 1, "(50, 0, 400)", "p_{T}^{#gamma 2}_{GEN} (GeV)", "", "", ""])
#plots.append(["gr_g1_p4_eta_norm1", "gr_g1_p4_eta", "", 1, "(60, -3., 3.)", "#eta^{#gamma 1}_{GEN}", "", "", ""])
#plots.append(["gr_g2_p4_eta_norm1", "gr_g2_p4_eta", "", 1, "(60, -3., 3.)", "#eta^{#gamma 2}_{GEN}", "", "", ""])
#plots.append(["gr_g1_p4_phi_norm1", "gr_g1_p4_phi", "", 1, "(63, -3.15, 3.15)", "#phi^{#gamma 1}_{GEN}", "", "", ""])
#plots.append(["gr_g2_p4_phi_norm1", "gr_g2_p4_phi", "", 1, "(63, -3.15, 3.15)", "#phi^{#gamma 2}_{GEN}", "", "", ""])
#plots.append(["jj_mass_normData", "jj_mass", "", "data", "(50, 0, 500)", "m_{jj} (GeV)", "", "", ""])
#plots.append(["regjj_mass_normData", "regjj_mass", "", "data", "(50, 0, 500)", "m_{jj}^{reg} (GeV)", "", "", ""])
#plots.append(["kinjj_mass_normData", "kinjj_mass", "", "data", "(50, 0, 500)", "m_{jj}^{kin} (GeV)", "", "", ""])
#plots.append(["regkinjj_mass_normData", "regkinjj_mass", "", "data", "(50, 0, 500)", "m_{jj}^{regkin} (GeV)", "", "", ""])
#plots.append(["jj_mass", "jj_mass", "", intL, "(50, 0, 500)", "m_{jj} (GeV)", "", "", ""])
#plots.append(["gg_mass", "gg_mass", "", intL, "(40, 100, 180)", "m_{#gamma#gamma} (GeV)", "", "", ""])
#plots.append(["jj_mass_norm1", "jj_mass", "", 1, "(50, 0, 500)", "m_{jj} (GeV)", "", "", ""])
#plots.append(["gg_mass_norm1", "gg_mass", "", 1, "(40, 100, 180)", "m_{#gamma#gamma} (GeV)", "", "", ""])
#plots.append(["pho1_e", "pho1_e", "", intL, "(500, 0, 500)", "e^{#gamma1} (GeV)", "", "", ""])
#plots.append(["pho2_e", "pho2_e", "", intL, "(500, 0, 500)", "e^{#gamma2} (GeV)", "", "", ""])
#plots.append(["jet1_e", "jet1_e", "", intL, "(500, 0, 500)", "e^{jet1} (GeV)", "", "", ""])
#plots.append(["jet2_e", "jet2_e", "", intL, "(500, 0, 500)", "e^{jet2} (GeV)", "", "", ""])
#plots.append(["jj_e", "jj_e", "", intL, "(500, 0, 500)", "e^{jj} (GeV)", "", "", ""])
#plots.append(["gg_e", "gg_e", "", intL, "(500, 0, 500)", "e^{#gamma#gamma} (GeV)", "", "", ""])
#plots.append(["pho1_r9", "pho1_r9", "", intL, "(100, 0, 5)", "r9^{#gamma1}", "", "", ""])
#plots.append(["pho2_r9", "pho2_r9", "", intL, "(100, 0, 5)", "r9^{#gamma2}", "", "", ""])
#plots.append(["ggjj_pt", "ggjj_pt", "", intL, "(500, 0, 500)", "p_{T}^{#gamma#gammajj} (GeV)", "", "", ""])
#plots.append(["ggjj_e", "ggjj_e", "", intL, "(1000, 0, 1000)", "e^{#gamma#gammajj} (GeV)", "", "", ""])
#plots.append(["ggjj_mass_normData", "ggjj_mass / 1000.", "", "data", "(50, 0, 1.)", "m_{#gamma#gammajj} (TeV)", "", "", ""])
#plots.append(["regggjj_mass_normData", "regggjj_mass / 1000.", "", "data", "(50, 0, 1.)", "m_{#gamma#gammajj}^{reg} (TeV)", "", "", ""])
#plots.append(["kinggjj_mass_normData", "kinggjj_mass / 1000.", "", "data", "(50, 0, 1.)", "m_{#gamma#gammajj}^{kin} (TeV)", "", "", ""])
#plots.append(["regkinggjj_mass_normData", "regkinggjj_mass / 1000.", "", "data", "(50, 0, 1.)", "m_{#gamma#gammajj}^{regkin} (TeV)", "", "", ""])
#plots.append(["ggjj_mass_normData", "ggjj_mass / 1000.", "", "data", "(50, 0, 1.)", "mass^{#gamma#gammajj} (TeV)", "", "", ""])
plots.append(["ggjj_mass_norm1", "ggjj_mass / 1000.", "", 1, "(50, 0, 1.)", "m_{#gamma#gammajj} (TeV)", "", "", ""])
#plots.append(["ggjj_mass", "ggjj_mass / 1000.", "", intL, "(50, 0, 1.)", "m_{#gamma#gammajj} (TeV)", "", "", ""])
#plots.append(["ggjj_phi", "ggjj_phi", "", intL, "(100, -5, 5)", "phi^{#gamma#gammajj}", "", "", ""])
#plots.append(["ggjj_eta", "ggjj_eta", "", intL, "(100, -10, 10)", "eta^{#gamma#gammajj}", "", "", ""])
#plots.append(["pho1_sieie", "pho1_sieie", "", intL, "(100, -0.5, 0.5)", "sieie^{#gamma1}", "", "", ""])
#plots.append(["pho2_sieie", "pho2_sieie", "", intL, "(100, -0.5, 0.5)", "sieie^{#gamma2}", "", "", ""])
#plots.append(["jet1_betaStarClassic", "jet1_betaStarClassic", "", intL, "(20, 0, 1)", "betaStarClassic^{jet1}", "", "", ""])
#plots.append(["jet2_betaStarClassic", "jet2_betaStarClassic", "", intL, "(20, 0, 1)", "betaStarClassic^{jet2}", "", "", ""])
#plots.append(["jet1_dR2Mean", "jet1_dR2Mean", "", intL, "(80,0, 0.2)", "dR2Mean^{jet1}", "", "", ""])
#plots.append(["jet2_dR2Mean", "jet2_dR2Mean", "", intL, "(80,0, 0.2)", "dR2Mean^{jet2}", "", "", ""])
#plots.append(["pho1_hoe", "pho1_hoe", "", intL, "(100,0, .05)", "hoe^{#gamma1}", "", "", ""])
#plots.append(["pho2_hoe", "pho2_hoe", "", intL, "(100,0, .05)", "hoe^{#gamma2}", "", "", ""])
#plots.append(["pho1_PFisoA_EBhigR9_norm1", "pho1_PFisoA", "( pho1_isEB) && (pho1_r9 > .94)", 1, "(100, 0, 10)", "PFisoA^{#gamma1}", "EB, R_{9} > .94",  6., ""])
#plots.append(["pho1_PFisoA_EBlowR9_norm1", "pho1_PFisoA", "( pho1_isEB) && (pho1_r9 < .94)", 1, "(100, 0, 10)", "PFisoA^{#gamma1}", "EB, R_{9} < .94", 4.7, ""])
#plots.append(["pho1_PFisoA_EEhigR9_norm1", "pho1_PFisoA", "(!pho1_isEB) && (pho1_r9 > .94)", 1, "(100, 0, 10)", "PFisoA^{#gamma1}", "EE, R_{9} > .94", 5.6, ""])
#plots.append(["pho1_PFisoA_EElowR9_norm1", "pho1_PFisoA", "(!pho1_isEB) && (pho1_r9 < .94)", 1, "(100, 0, 10)", "PFisoA^{#gamma1}", "EE, R_{9} < .94", 3.6, ""])
#plots.append(["pho1_PFisoB_EBhigR9_norm1", "pho1_PFisoB", "( pho1_isEB) && (pho1_r9 > .94)", 1, "(150,-5, 10)", "PFisoB^{#gamma1}", "EB, R_{9} > .94", 10., ""])
#plots.append(["pho1_PFisoB_EBlowR9_norm1", "pho1_PFisoB", "( pho1_isEB) && (pho1_r9 < .94)", 1, "(150,-5, 10)", "PFisoB^{#gamma1}", "EB, R_{9} < .94", 6.5, ""])
#plots.append(["pho1_PFisoB_EEhigR9_norm1", "pho1_PFisoB", "(!pho1_isEB) && (pho1_r9 > .94)", 1, "(150,-5, 10)", "PFisoB^{#gamma1}", "EE, R_{9} > .94", 5.6, ""])
#plots.append(["pho1_PFisoB_EElowR9_norm1", "pho1_PFisoB", "(!pho1_isEB) && (pho1_r9 < .94)", 1, "(150,-5, 10)", "PFisoB^{#gamma1}", "EE, R_{9} < .94", 4.4, ""])
#plots.append(["pho2_PFisoA_EBhigR9_norm1", "pho2_PFisoA", "( pho2_isEB) && (pho2_r9 > .94)", 1, "(100, 0, 10)", "PFisoA^{#gamma2}", "EB, R_{9} > .94",  6., ""])
#plots.append(["pho2_PFisoA_EBlowR9_norm1", "pho2_PFisoA", "( pho2_isEB) && (pho2_r9 < .94)", 1, "(100, 0, 10)", "PFisoA^{#gamma2}", "EB, R_{9} < .94", 4.7, ""])
#plots.append(["pho2_PFisoA_EEhigR9_norm1", "pho2_PFisoA", "(!pho2_isEB) && (pho2_r9 > .94)", 1, "(100, 0, 10)", "PFisoA^{#gamma2}", "EE, R_{9} > .94", 5.6, ""])
#plots.append(["pho2_PFisoA_EElowR9_norm1", "pho2_PFisoA", "(!pho2_isEB) && (pho2_r9 < .94)", 1, "(100, 0, 10)", "PFisoA^{#gamma2}", "EE, R_{9} < .94", 3.6, ""])
#plots.append(["pho2_PFisoB_EBhigR9_norm1", "pho2_PFisoB", "( pho2_isEB) && (pho2_r9 > .94)", 1, "(150,-5, 10)", "PFisoB^{#gamma2}", "EB, R_{9} > .94", 10., ""])
#plots.append(["pho2_PFisoB_EBlowR9_norm1", "pho2_PFisoB", "( pho2_isEB) && (pho2_r9 < .94)", 1, "(150,-5, 10)", "PFisoB^{#gamma2}", "EB, R_{9} < .94", 6.5, ""])
#plots.append(["pho2_PFisoB_EEhigR9_norm1", "pho2_PFisoB", "(!pho2_isEB) && (pho2_r9 > .94)", 1, "(150,-5, 10)", "PFisoB^{#gamma2}", "EE, R_{9} > .94", 5.6, ""])
#plots.append(["pho2_PFisoB_EElowR9_norm1", "pho2_PFisoB", "(!pho2_isEB) && (pho2_r9 < .94)", 1, "(150,-5, 10)", "PFisoB^{#gamma2}", "EE, R_{9} < .94", 4.4, ""])
#plots.append(["pho1_isconv", "pho1_isconv", "", intL, "(100,0, 1)", "isconv^{#gamma1}", "", "", ""])
#plots.append(["pho2_isconv", "pho2_isconv", "", intL, "(100,0, 1)", "isconv^{#gamma2}", "", "", ""])
#plots.append(["jet1_csvBtag", "jet1_csvBtag", "", intL, "(100, 0, 1)", "csvBtag^{jet1}", "", "", ""])
#plots.append(["jet2_csvBtag", "jet2_csvBtag", "", intL, "(100, 0, 1)", "csvBtag^{jet2}", "", "", ""])
#plots.append(["pho1_IDmva_EB_norm1", "pho1_IDmva", "( pho1_isEB)", 1, "(50,-.5, .5)", "ID MVA_{#gamma1}", "EB", 0.02, ""])
#plots.append(["pho1_IDmva_EE_norm1", "pho1_IDmva", "(!pho1_isEB)", 1, "(50,-.5, .5)", "ID MVA_{#gamma1}", "EE", 0.1, ""])
#plots.append(["pho2_IDmva_EB_norm1", "pho2_IDmva", "( pho2_isEB)", 1, "(50,-.5, .5)", "ID MVA_{#gamma2}", "EB", 0.02, ""])
#plots.append(["pho2_IDmva_EE_norm1", "pho2_IDmva", "(!pho2_isEB)", 1, "(50,-.5, .5)", "ID MVA_{#gamma2}", "EE", 0.1, ""])




for name2, variable, plot_cut, norm, binning, title, additional_info, cutline, cutline2 in plots:
    c1 = TCanvas()
    legend = TLegend(0.45, 0.82, 0.90, 0.93, "")
    legend.SetTextSize(0.025)
    legend.SetFillColor(ROOT.kWhite)
    legend.SetLineColor(ROOT.kWhite)
    legend.SetShadowColor(ROOT.kWhite)
    xnbin, xlow, xhigh = map(float, binning.strip().strip("()").split(","))
    ymax = -1
    ymin = 10000000
    firsthistname = ""
    if plot_cut == "": plot_cut = "1"
    hist_signal = {}
    hist_data = {}
    hist_bkg = {}
    label_signal = {}
    label_data = {}
    label_bkg = {}

    for ifile, [ name, typ, dirpath, subdir, file, tree, sample_cut, color, style, label , sigma , N] in enumerate(samples):
#        print ""
#        print ifile, file, color, style, label, typ
        chain = TChain(tree)
        chain.Add( path.join(dirpath, subdir, file) )
        total_cut = plot_cut
        if sample_cut == "": sample_cut = "1"
        if typ < 0:
            total_cut = "(" + plot_cut + ") * (" + str(sigma) + " * " + str(intL) + ")/" + str(N)
        elif typ == 0:
           total_cut = "(" + plot_cut + ") * (" + sample_cut + ")"
        elif typ > 0:
           total_cut = "(" + plot_cut + ") * (" + sample_cut + ")"
        option = ""
        if ifile != 0:
            option = "same"
        if typ == 0:
            option += "e1"
        chain.Draw(variable + ">>h_tmp" + binning, total_cut, option)
        # Cosmetics
        h = ROOT.gDirectory.Get("h_tmp")
#        print h.GetEntries()
        try:
            h.SetName(name + "_" + name2 + "_" + str(ifile))
        except AttributeError:
            print "#INFO: Empty histogram for contribution ", name + "_" + name2 + "_" + str(ifile)
            continue
        if ifile == 0:
            firsthistname = name + "_" + name2 + "_" + str(ifile)
        h.SetLineWidth(2)
        h.SetLineColor(color)
        h.SetFillColor(color)
        h.SetFillStyle(style)
        h.GetXaxis().SetTitle( title )
        unit = ""
        if title.find("(") != -1:
            unit = title[title.find("(")+1:title.find(")")]
        if norm == 1. or norm == 1:
            h.GetYaxis().SetTitle( "Norm. to unity / ( " + str(((xhigh - xlow) / xnbin)) + " " + unit + " )")
        elif norm == "data" or norm == "Data":
            h.GetYaxis().SetTitle( "Norm. to data / ( " + str(((xhigh - xlow) / xnbin)) + " " + unit + " )")
        else:
            h.GetYaxis().SetTitle( "# events / ( " + str(((xhigh - xlow) / xnbin)) + " " + unit + " )")
        # store histo for redraw in the correct order later
        if typ > 0:
            label_bkg[typ] = label
            if typ not in hist_bkg:
                hist_bkg[typ] = h
            else:
                hist_bkg[typ].Add(h)
        elif typ == 0:
            label_data[typ] = label
            hist_data[typ] = h
        elif typ < 0:
            label_signal[typ] = label
            hist_signal[typ] = h
        del chain, h

#        print hist_bkg
#        print hist_signal
#        print hist_data

    # Sum the backgrounds
#    print ""
#    print "1: ", hist_bkg.items()
#    print "2: ", sorted(hist_bkg.items())
#    print "3: ", collections.OrderedDict(sorted(hist_bkg.items()))
    for key in collections.OrderedDict(sorted(hist_bkg.items())):
#        print "hist_bkg[key].GetEntries()= ", hist_bkg[key].GetEntries()
        for jkey in collections.OrderedDict(sorted(hist_bkg.items())):
            if jkey <= key: continue
            hist_bkg[key].Add(hist_bkg[jkey])
#            print "hist_bkg[key].GetEntries()= ", hist_bkg[key].GetEntries()
    # Adjust norm if case happens
    if norm == 1. or norm == 1:
        bkg_integral = 1.
        for ikey, key in enumerate(collections.OrderedDict(sorted(hist_bkg.items()))):
            if ikey == 0:
                bkg_integral = hist_bkg[key].Integral(0, hist_bkg[key].GetNbinsX() + 1)
            hist_bkg[key].Scale( 1. / bkg_integral )
        data_integral = 1.
        for ikey, key in enumerate(collections.OrderedDict(sorted(hist_data.items()))):
            if ikey == 0:
                data_integral = hist_data[key].Integral(0, hist_data[key].GetNbinsX() +1)
            hist_data[key].Scale( 1. / data_integral )
        signal_integral = 1.
        for ikey, key in enumerate(collections.OrderedDict(sorted(hist_signal.items()))):
            if ikey == 0:
                signal_integral = hist_signal[key].Integral(0, hist_signal[key].GetNbinsX() +1)
            hist_signal[key].Scale( 1. / signal_integral )
    elif norm == "data" or norm == "Data":
        data_integral = 1.
        for ikey, key in enumerate(collections.OrderedDict(sorted(hist_data.items()))):
            if ikey == 0:
                data_integral = hist_data[key].Integral(0, hist_data[key].GetNbinsX() +1)
            else:
                continue
#        print "data_integral= ", data_integral
        bkg_integral = 1.
        for ikey, key in enumerate(collections.OrderedDict(sorted(hist_bkg.items()))):
#            print ikey, key, hist_bkg[key].GetEntries(), hist_bkg[key].Integral(0, hist_bkg[key].GetNbinsX() + 1)
            if ikey == 0:
                bkg_integral = hist_bkg[key].Integral(0, hist_bkg[key].GetNbinsX() + 1)
            hist_bkg[key].Scale( data_integral / bkg_integral )
        signal_integral = 1.
        for ikey, key in enumerate(collections.OrderedDict(sorted(hist_signal.items()))):
            if ikey == 0:
                signal_integral = hist_signal[key].Integral(0, hist_signal[key].GetNbinsX() +1)
            hist_signal[key].Scale( data_integral / signal_integral )
    # redraw in order : background, data, signal, axis
    if len(hist_bkg) + len(hist_data) + len(hist_signal) > 1:
        legend.SetNColumns(2)
    if len(hist_bkg) + len(hist_data) + len(hist_signal) > 6:
        legend.SetNColumns(3)
    for ikey, key in enumerate(collections.OrderedDict(sorted(hist_bkg.items()))):
        if ikey == 0:
            hist_bkg[key].Draw("")
            firsthistname = hist_bkg[key].GetName()
        else:
            hist_bkg[key].Draw("same")
        legend.AddEntry(hist_bkg[key].GetName(), label_bkg[key], "lf")
        ymax = max(ymax, hist_bkg[key].GetMaximum())
        ymin = min(ymin, hist_bkg[key].GetMinimum(0.0))
    for key in hist_data:
        hist_data[key].Draw("e1same")
        legend.AddEntry(hist_data[key].GetName(), label_data[key], "lpe")
        ymax = max(ymax, hist_data[key].GetMaximum())
        ymin = min(ymin, hist_data[key].GetMinimum(0.0))
    for key in collections.OrderedDict(sorted(hist_signal.items())):
        hist_signal[key].Draw("same")
        legend.AddEntry(hist_signal[key].GetName(), label_signal[key], "lf")
        ymax = max(ymax, hist_signal[key].GetMaximum())
        ymin = min(ymin, hist_signal[key].GetMinimum(0.0))
    ymin_lin = ymin / 10.
    yrange_lin = ymax - ymin_lin
    ymax_lin = .25 * yrange_lin + ymax
    yrange_log = (log10(ymax) - log10(ymin)) / .77
    ymax_log = pow(10., .25*yrange_log + log10(ymax))
    ymin_log = pow(10., log10(ymin) - .03*yrange_log)

    latexLabel = TLatex()
    latexLabel.SetTextSize(.03)
    latexLabel.SetNDC()
    latexLabel.DrawLatex(.25, .96, "CMS Internal     L = 19.7 fb^{-1}     #sqrt{s} = 8 TeV")
    latexLabel.DrawLatex(.20, .85, additional_info)
    ROOT.gPad.RedrawAxis()
    legend.Draw()
    c1.Update()

    line = TLine()
    line.SetLineStyle(2)
    line.SetLineWidth(2)
    line2 = TLine()
    line2.SetLineStyle(2)
    line2.SetLineWidth(2)

    h = ROOT.gDirectory.Get(firsthistname)
    h.SetMaximum(ymax_lin)
    h.SetMinimum(ymin_lin)
    if cutline != "":
        line.SetX1(cutline); line.SetY1(ymin_lin); line.SetX2(cutline); line.SetY2(ymax)
        line.Draw("same")
    if cutline2 != "":
        line2.SetX1(cutline2); line2.SetY1(ymin_lin); line2.SetX2(cutline2); line2.SetY2(ymax)
        line2.Draw("same")
    c1.Update()
    c1.Print("png/" + name2 + ".png")
    c1.Print("pdf/" + name2 + ".pdf")
    c1.Print("gif/" + name2 + ".gif")
    c1.Print("root/" + name2 + ".root")


    c1.SetLogy(1)
    h.SetMaximum(ymax_log)
    h.SetMinimum(ymin_log)
    h.GetYaxis().SetRangeUser(ymin_log, ymax_log)
    if cutline != "":
        line.SetX1(cutline); line.SetY1(ymin_log); line.SetX2(cutline); line.SetY2(ymax)
        line.Draw("same")
    if cutline2 != "":
        line2.SetX1(cutline2); line2.SetY1(ymin_log); line2.SetX2(cutline2); line2.SetY2(ymax)
        line2.Draw("same")
    c1.Update()
    c1.Print("png/" + name2 + "_log.png")
    c1.Print("pdf/" + name2 + "_log.pdf")
    c1.Print("gif/" + name2 + "_log.gif")
    c1.Print("root/" + name2 + "_log.root")
    c1.SetLogy(0)

    del c1

