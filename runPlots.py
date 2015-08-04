#!/nfs/soft/python/python-2.7.5-sl6_amd64_gcc44/bin/python
#// Small dumb code to play with trees
#// O.Bondu, F. Bojarski (May 2014)
# Various python imports
import argparse
import os, sys
import json
from math import log10, pow
import collections
# import SAMADhi stuff
CMSSW_BASE = os.environ['CMSSW_BASE']
SCRAM_ARCH = os.environ['SCRAM_ARCH']
sys.path.append(os.path.join(CMSSW_BASE,'bin', SCRAM_ARCH))
from SAMADhi import Dataset, Sample, DbStore
# ROOT setup
import ROOT
from ROOT import TFile, TTree, TLine, TChain, TCanvas, TH1D, TLatex, TLegend, TLorentzVector
ROOT.gROOT.Reset()
ROOT.gROOT.SetBatch()
ROOT.gROOT.ProcessLine(".x setTDRStyle.C")
ROOT.TGaxis.SetMaxDigits(3)


def get_options():
    """
    Parse and return the arguments provided by the user.
    """
    parser = argparse.ArgumentParser(description='Plotter')
    parser.add_argument('-s', '--samples', type=str, required=True, action='append', dest='samples', metavar='FILE',
                        help='samples which are to be considered for the plots')
    parser.add_argument('-p', '--plots', type=str, required=True, action='append', dest='plots', metavar='FILE',
                        help='plots which are to be done')
    parser.add_argument('--intL', type=float, required=True, dest='intL',
                        help='amount of integrated luminosity (in pb)')
    options = parser.parse_args()
    return options

def get_sample(inputSample):
    dbstore = DbStore()
    resultset = dbstore.find(Sample, Sample.name==inputSample)
    return list(resultset.values(Sample.path, Sample.normalization, Sample.nevents_processed))

def main(samples, plots, intL):
    c1 = TCanvas()
    for kplot in plots:
        print "\tNow taking care of plot", kplot
        name2 = str(kplot)
        variable = str(plots[kplot]["variable"])
        plot_cut = str(plots[kplot]["plot_cut"])
        norm = plots[kplot]["norm"]
        binning = str(plots[kplot]["binning"])
        title = str(plots[kplot]["xtitle"])
        unit = str(plots[kplot]["unit"])
        additional_info = str(plots[kplot]["additional_info"])
        cutline = str(plots[kplot]["cutline"])
        cutline2 = str(plots[kplot]["cutline2"])
        
        c1 = TCanvas()
        legend = TLegend(0.45, 0.82, 0.90, 0.93, "")
        legend.SetTextSize(0.015)
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
    
        for ifile, ksample in enumerate(samples):
            name = str(ksample)
            typ = samples[ksample]["type"]
            dirpath = samples[ksample]["path"]
            subdir = ""
            file = "output*root"
            tree = str(samples[ksample]["tree_name"])
            sample_cut = str(samples[ksample]["sample_cut"])
            color = samples[ksample]["color"]
            style = samples[ksample]["style"]
            label = str(samples[ksample]["label"])
            sigma = samples[ksample]["norm"]
            N = samples[ksample]["nevents"]
            sumweights = samples[ksample]["sumweights"]


    #        print ""
    #        print ifile, file, color, style, label, typ
            chain = TChain(tree)
            chain.Add( os.path.join(dirpath, subdir, file) )
            total_cut = plot_cut
            if sample_cut == "": sample_cut = "1"
            if typ < 0:
                total_cut = "(" + plot_cut + ") * event_weight * (" + str(sigma) + " * " + str(intL) + ")/" + str(sumweights)
            elif typ == 0:
               total_cut = "(" + plot_cut + ") * (" + sample_cut + ")"
            elif typ > 0:
               total_cut = "(" + plot_cut + ") * (" + sample_cut + ")"
#            print total_cut
            option = ""
            if ifile != 0:
                option = "same"
            if typ == 0:
                option += "e1"
            print "\tCore draw of histogram for contribution", name,
            chain.Draw(variable + ">>h_tmp" + binning, total_cut, option)
            print "... done"
#            print "\t\tEnd draw"
            # Cosmetics
            h = ROOT.gDirectory.Get("h_tmp")
    #        h.UseCurrentStyle()
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
            h.SetMarkerColor(color)
            h.SetMarkerSize(1)
            h.SetMarkerStyle(1)
            h.GetXaxis().SetTitle( title )
            if len(unit) > 0:
                h.GetXaxis().SetTitle( title + " (" + unit + ")")
#            unit = ""
#            if title.find("[") != -1:
#                unit = title[title.find("[")+1:title.find("]")]
            unit = " " + unit
            if norm == 1. or norm == 1:
                h.GetYaxis().SetTitle( "Norm. to unity / ( " + str(((xhigh - xlow) / xnbin)) + unit + " )")
            elif norm == "data" or norm == "Data":
                h.GetYaxis().SetTitle( "Norm. to data / ( " + str(((xhigh - xlow) / xnbin)) + unit + " )")
            else:
                h.GetYaxis().SetTitle( "# events / ( " + str(((xhigh - xlow) / xnbin)) + unit + " )")
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
    
    #        print "hist_bkg=", hist_bkg
    #        print "hist_signal=", hist_signal
    #        print "hist_data=", hist_data
    
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
#                if ikey == 0:
                signal_integral = hist_signal[key].Integral(0, hist_signal[key].GetNbinsX() +1)
#                print "signal_integral=", signal_integral
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
        for key in collections.OrderedDict(sorted(hist_signal.items(), reverse=True)):
            hist_signal[key].Draw("histsame")
            ROOT.gPad.Modified()
            c1.Update()
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
        latexLabel.SetTextSize(0.75 * c1.GetTopMargin())
        latexLabel.SetNDC()
        latexLabel.SetTextFont(42) # helvetica
        if norm == 1.:
            latexLabel.DrawLatex(0.80, 0.96, "(13 TeV)")
        else:
            if intL > 1000.:
                latexLabel.DrawLatex(0.70, 0.96, str(intL) + "/fb (13 TeV)")
            else:
                latexLabel.DrawLatex(0.70, 0.96, str(intL) + "/pb (13 TeV)")
        latexLabel.SetTextFont(61) # helvetica bold face
        latexLabel.DrawLatex(0.17, 0.89, "CMS")
        latexLabel.SetTextFont(52) # helvetica italics
        latexLabel.DrawLatex(0.25, 0.89, "Internal")
        latexLabel.SetTextSize(.04)
        latexLabel.DrawLatex(.17, .82, additional_info)
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

def color_as_int(color):
    # from https://root.cern.ch/root/html/Rtypes.h, because it's a pain to encode this into a json
    colordict = {"kWhite":"0", "kBlack":"1", "kGray":"920",
              "kRed"   :"632", "kGreen" :"416", "kBlue":"600", "kYellow":"400", "kMagenta":"616", "kCyan":"432",
              "kOrange":"800", "kSpring":"820", "kTeal":"840", "kAzure" :"860", "kViolet" :"880", "kPink":"900" }
    color = str(color)
    for key in colordict:
        color = color.replace(key, colordict[key])
    return eval(color)

def get_sumweights(tree_name, path):
    c1 = TCanvas()
    chain = TChain(str(tree_name))
    chain.Add(os.path.join(str(path), "output*root"))
    chain.Draw("event_weight>>h_tmp")
    h = ROOT.gDirectory.Get("h_tmp")
    sumweights = h.Integral()
    del c1
    return sumweights

if __name__ == '__main__':
    options = get_options()
    print "##### Read samples to be processed"
    samples = {}
    for sample in options.samples:
        with open(sample) as f:
            samples.update(json.load(f))
    for ksample in samples:
        samples[ksample]["color"] = color_as_int(samples[ksample]["color"])
        path, norm, nevents = get_sample(samples[ksample]["db_name"])[0]
        samples[ksample]["path"] = str(path)
        try: # if norm is defined in the json, then take precedence over the database
            norm = samples[ksample]["norm"]
        except KeyError:
            samples[ksample]["norm"] = norm
        samples[ksample]["nevents"] = nevents
        samples[ksample]["sumweights"] = get_sumweights(samples[ksample]["tree_name"], path)
        print "\t", ksample, "nevents=", nevents, "sumweights=", samples[ksample]["sumweights"]
    print "##### Read plots to be processed"
    plots = {}
    for plot in options.plots:
        with open(plot) as f:
            plots.update(json.load(f))
    print "##### Now plotting"
    main(samples, plots, options.intL)
