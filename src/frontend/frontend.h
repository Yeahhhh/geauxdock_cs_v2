#ifndef FRONTEND_H
#define FRONTEND_H

#include <string>
#include <vector>
#include <sstream>

#include <geauxdock.h>

using namespace std;


void Usage (char *);
void Banner ();
void SetMcLog (McLog *);



void DumpRecord (const Record *, const int, const char*);

vector<string> tokenlize(string & line);



template <typename T>
string num2string (T n)
{
    ostringstream oss;
    oss << n;
    return oss.str();
}




class ParaParser {
   protected:
       std::vector<std::string> tokens;

       InputFiles inputfiles;
       ExchgPara exchgpara;
       McPara mcpara;

   public:
       //ParaParser();
       //~ParaParser();
       void parse(std::string);
       std::vector<std::string> get_tokens() { return tokens; };
       McPara get_mcpara() { return mcpara; };
};





class Loader : public ParaParser {

protected:
    // meta data
    InputFiles inputfiles;
    ComplexSize sz;


    // the follows elements are resued among the data set
    Protein0 *prt0;
    Protein *prt;
    EnePara0 *enepara0;
    EnePara *enepara;

    // the follows elements are different among the data set
    Ligand0 *lig0;
    Psp0 *psp0;
    Kde0 *kde0;
    Mcs0 *mcs0;
    Ligand *lig;
    Psp *psp;
    Kde *kde;
    Mcs *mcs;
    Mcs_R *mcs_r;
    Mcs_ELL *mcs_ell;
    Mcs_CSR *mcs_csr;


    Temp *temp;
    ReplicaMC *replica;




    bool is_identical_target();
    void assign_new_target();
    void set_temperature();
    void set_replica();


public:
    Loader();
    ~Loader();

    void load_target();
    void load_ligand();
    void load(std::string);
    void check();
    void print_sz();
    void build_complex(Complex *);
    ComplexSize get_sz() { return sz; };
};



#endif // FRONTEND_H

