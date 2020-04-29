#ifndef UTILS_H
#define UTILS_H

#include "config.h"
#include "AnalyseCenter.h"
#include "Satellite.h"

#include <vector>
#include <string>
#include <algorithm>

std::string replace_pattern(const std::string &pattern, MJD t,
                            const std::string &prefix=std::string(),
                            const std::string &suffix=std::string());

bool init_acs(const config_t &config, std::vector<AnalyseCenter> &acs, AnalyseCenter &combined_ac);

bool init_sats(const std::vector<std::string> &prns, std::vector<Satellite> &sats);

bool construct_initclk(const config_t &config,
                       const std::vector<AnalyseCenter> &acs,
                       const std::vector<Satellite> &sats,
                       std::vector<std::vector<double>> &comb_clks);

bool align_widelane(const std::vector<Satellite> &sats,
                    std::vector<AnalyseCenter> &acs,
                    const std::vector<int> &prns);

void count_satclks(const config_t &config,
                   const std::vector<std::vector<double>> &sat_clks,
                   std::vector<size_t> &counts);

void remove_clock_datum(std::vector<std::vector<double>> &sat_clks,
                        const std::vector<int> &adjust_prns,
                        const std::vector<int> &common_prns);

double satclk_std(const std::vector<double> &clks, const std::vector<double> &refs, double T);

// void remove_clock_bias(const std::string &prn,
void remove_clock_bias(const std::string &name, const std::string &prn,
                       std::vector<double> &sat_clks,
                       const std::vector<double> &ref_clks,
                       bool phase_clock,
                       double &std, bool edit);

void combine_one_epoch(const std::vector<double> &clks,
                       const std::vector<double> &wgts,
                       double &mean,
                       double &wrms,
                       std::vector<int> &deleted);

void write_satclks(FILE *fp, const config_t &config, const std::string &acn,
                   const std::vector<std::vector<double>> &sat_clks);

void compare_satclks(const config_t &config,
                     const std::vector<std::vector<double>> &sat_clks,
                     const std::vector<std::vector<double>> &ref_clks);

bool write_clkfile(const std::string &path, MJD t, int length, int interval,
                   const std::vector<std::string> &prns,
                   const std::vector<std::vector<double>> &satclks);

bool write_bias(const std::string &path, MJD t,
                const std::vector<std::string> &prns,
                const std::vector<double> &wl_bias);

double weighted_mean(const std::vector<double> &vals, const std::vector<double> &wgts, double &wrms);

double median(const std::vector<double> &vals);

void unit_weight(std::vector<double> &wgts);

bool sat_freq(const std::string &prn, double f[]);

#endif // UTILS_H
