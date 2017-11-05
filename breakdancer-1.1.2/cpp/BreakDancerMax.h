#include <iostream>
#include <fstream>
#include <strstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <list>
#include <iomanip>
#include <cmath>
#include <math.h>
#include <time.h>
#include <map>
#include <assert.h>
#include <sstream>
#include "sam.h"
#include "bam.h"
#include "ksort.h"
#include "khash.h"
#include "AlnParser.h"
#include "Poisson.h"
#include "samtools.h"

using namespace std;

#define LZERO -99;

#define ZERO exp(LZERO);

/*template <class T>
T from_string(const std::string& s, 
                 std::ios_base& (*f)(std::ios_base&))*/
void do_break_func(vector<vector<string> > &reg_seq, map<int,vector<int> > &reg_name, map<string,vector<int> > &read, map<int, vector<vector<string> > > &regs, int *begins, int *beginc, int *lasts, int *lastc, int *idx_buff, int buffer_size, int *nnormal_reads, int min_len, int *reg_idx, int transchr_rearrange, int min_map_qual, int Illumina_long_insert, string prefix_fastq, map<uint32_t, map<string,int> > &x_readcounts, uint32_t reference_len, int fisher, map<string,string> &ReadsOut, map<string,float> &mean_insertsize, map<string, string> &SVtype, map<string, int> &mapQual, map<string, float> &uppercutoff, map<string, float> &lowercutoff, int max_sd, int d, int min_read_pair, string dump_BED, int *max_readlen, samfile_t *in, int seq_coverage_lim, uint32_t *ntotal_nucleotides, map<string, uint32_t> &nread_ROI, map<int, map<string, uint32_t> > &read_count_ROI_map, map<string, uint32_t> &nread_FR, map<int, map<string, uint32_t> > &read_count_FR_map, map<string, float> &read_density,int CN_lib, map<string, string> libmaps, vector<string> maps, int print_AF, int score_threshold);

void Analysis (string lib, bam1_t *b, vector<vector<string> > &reg_seq, map<int,vector<int> > &reg_name, map<string,vector<int> > &read, map<int, vector<vector<string> > > &regs, int *begins, int *beginc, int *lasts, int *lastc, int *idx_buff, int buffer_size, int *nnormal_reads, int min_len, int *normal_switch, int *reg_idx, int transchr_rearrange, int min_map_qual, int Illumina_long_insert, string prefix_fastq, map<uint32_t, map<string,int> > &x_readcounts, uint32_t reference_len, int fisher, map<string,string> &ReadsOut, map<string,float> &mean_insertsize, map<string, string> &SVtype, map<string, int> &mapQual, map<string,float> &uppercutoff, map<string,float> &lowercutoff, int max_sd, int d, int min_read_pair, string dump_BED, int *max_readlen, string ori, samfile_t *in, int seq_coverage_lim, uint32_t *ntotal_nucleotides, map<string, uint32_t> &nread_ROI, map<int, map<string, uint32_t> > &read_count_ROI_map, map<string, uint32_t> &nread_FR, map<int, map<string, uint32_t> > &read_count_FR_map, map<string, float> &read_density, /*map<string, map<string, vector<int> > > &nread_ROI_debug, map<int, map<string, map<string, vector<int> > > > &read_count_ROI_debug, map<string, map<string, vector<int> > > &nread_FR_debug, map<int, map<string, map<string, vector<int> > > > &read_count_FR_debug, int *possible_fake, */map<string, uint32_t> &possible_fake_data/*, map<string, map<string, vector<int> > > & possible_fake_data_debug*/, int CN_bam, map<string, string> libmaps, vector<string> maps, int print_AF, int score_threshold);

void buildConnection(map<string,vector<int> > &read, map<int,vector<int> > &reg_name, map<int,vector<vector<string> > > &regs, map<uint32_t, map<string,int> > &x_readcounts, uint32_t reference_len, int fisher, int min_read_pair, string dump_BED, int max_readlen, string prefix_fastq, map<string,string> &ReadsOut, map<string,string> &SVtype, map<string,float> &mean_insertsize, samfile_t *in, map<int, map<string, uint32_t> > &read_count_ROI_map, map<int, map<string, uint32_t> > &read_count_FR_map, map<string, float> &read_density, int CN_bam, vector<string> maps, int print_AF, int score_threshold, map<string, string> libmaps);//, map<int, map<string, map<string, int> > > &read_count_ROI_debug, map<int, map<string, map<string, int> > > &read_count_FR_debug);

float ComputeProbScore(vector<int> &rnode, map<string,int> &rlibrary_readcount, uint32_t type, map<uint32_t, map<string,int> > &x_readcounts, uint32_t reference_len, int fisher, map<int, vector<int> > &reg_name);

void EstimatePriorParameters(map<string,string> &fmaps, map<string,string> &readgroup_library, map<string, float> &mean_insertsize, map<string, float> &std_insertsize, map<string,float> &uppercutoff, map<string,float> &lowercutoff, map<string,float> &readlens, string chr, int cut_sd, int min_map_qual, map<string, string> &readgroup_platform, string platform);

float mean(vector<int> &stat);

float standard_deviation(vector<int> &stat, float mean);

int PutativeRegion(vector<int> &rnode, map<int,vector<int> > &reg_name);

pair64_t * ReadBamChr_prep(string chr_str, string bam_name, int *tid, int *beg, int *end, samfile_t *in, int *n_off);

int ReadBamChr(bam1_t *b, bamFile fp, int tid, int beg, int end, uint64_t *curr_off, int *i, int *n_seeks, pair64_t *off, int n_off);

int MergeBams_prep(string *fn, int n, samfile_t **in, heap1_t *heap, uint64_t *idx);

int MergeBamsChr_prep(string *fn, int n, bamFile *fp, heap1_t *heap, string chr_str, int *tid, int *beg, int *end, samfile_t **in, pair64_t **off, int *n_off, uint64_t *idx);

string get_from_line(string line,string search,int flag);

string get_from_line_two(string line,string search1,string search2,int flag2);

/*string itoa(int i);

int atoi(string str);

float atof(string str);*/

string itos(int i);

string get_string_qual(uint8_t *pt, int32_t length);

string get_string(uint8_t *pt, int32_t length);

string get_string_qual(uint8_t *pt, int32_t length);

string search_more(string line, string search, 	size_t pos_begin);

string char2str(char *str_);

