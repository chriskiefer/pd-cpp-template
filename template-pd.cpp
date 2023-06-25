#include "m_pd.h"
#include <cmath>
#include <fstream>

using namespace std;


static t_class *template_pd_class;


class template_pd {
public:
    
    int testint;
    typedef struct _template_pd {
        t_object  x_obj;
        template_pd *f;
        t_outlet *out0;
    } t_template_pd;


    bool needToInitialise;
    
    template_pd(t_template_pd *x) {
        init(x);
    }
    
    static void bang_proxy(t_template_pd *x) {
        x->f->bang(x);
    }

    void bang(t_template_pd *x) {
    }
    
    
    void init(t_template_pd *x) {
        needToInitialise = false;
        post("Initialised");
    }
    
    static void * create_new(t_symbol *selector, int argcount, t_atom *argvec)
    {
        t_template_pd *x = (t_template_pd *)pd_new(template_pd_class);
        post("Create: %d", argcount);
        if (argcount != 1) {
            pd_error(x, "Incorrect number of arguments");
        }
        post("t_template_pd: initialised");
        return (void *)x;
    }

    static void free(t_template_pd *x)
    {
        if (x->f) {
            delete x->f;
        }
    }
};



extern "C" __attribute__((visibility("default"))) void pd_external_setup() {
    
    template_pd_class = class_new(gensym("template_ext"),
                               (t_newmethod)template_pd::create_new,
                               (t_method)template_pd::free, sizeof(template_pd::t_template_pd),
                               CLASS_DEFAULT, A_GIMME, A_NULL);
    class_addbang(template_pd_class, template_pd::bang_proxy);    

}

