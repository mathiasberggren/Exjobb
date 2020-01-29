#ifndef LINEAR_MODEL
#define LINEAR_MODEL

#include <vector>
#include <utility>

typedef std::vector< std::pair<std::vector<double>, double> > Training_data;

class LinearModel
{
    public:
        LinearModel(double learning_rate = 0.01);
        double predict(double x1, double x2)const;
        double loss(Training_data const& train_data)const;
        void fit(Training_data const&, int epochs = 1);
        void dump(std::string const& filename )const;
        void import(std::string const& filename);
    private:
        inline double residual(double x1, double x2, double y)const;
        /* Sum of squared residuals as loss function */
        inline double loss(double x1, double x2, double y)const;
        inline double der_loss_k1(double x1, double x2, double y)const;
        inline double der_loss_k2(double x1, double x2, double y)const;
        inline double der_loss_m(double x1, double x2, double y)const;

        double learning_rate;

        double change_k1;
        double change_k2;
        double change_m;

        double k1;
        double k2; 
        double m;

};


#endif
