/* Made by Mathias Berggren (mathiasberggren1@gmail.com)
 * Inspired by 
 * https://docs.opencv.org/2.4/modules/ml/doc/decision_trees.html
 */

#ifndef REGRESSION_TREE
#define REGRESSION_TREE

#include <utility>
#include <vector>

typedef std::vector< std::pair<std::vector<double>, double> > Training_data;

class RegressionTree
{
    private:
        struct Node;
        struct Split;
    public:
        RegressionTree(unsigned depth = 10, unsigned leaf_k = 5);
        RegressionTree(RegressionTree const&) = default;
        ~RegressionTree();
        RegressionTree& operator=(RegressionTree const&) = default;
        double predict(double x1, double x2)const;
        void set_leaf_threshold(unsigned leaf) { leaf_threshold = leaf; }
        void set_max_depth(unsigned depth) { max_depth = depth; }
        void train(Training_data const&);
        double loss(Training_data const&)const;
        void dump(std::string const& filename)const;
        void import(std::string const& filename);
    private:
        void train(Node*& element, Training_data const&, Node* const& parent = nullptr);
        unsigned max_depth; 
        unsigned leaf_threshold;
        Node* root; 

        struct Node
        {
            struct Split
            {
                Split(double threshold, unsigned feature);
                inline bool predict(double x1, double x2)const;
                unsigned var_idx;
                double threshold;
                std::string to_string()const;
            };

            Node(); 
            Node(Node* const&); 
            Node(Node const&) = default; 
            Node& operator=(Node const&) = default;
            Node(Node* const&, Split* const&); 
            Node(Split* const&); 
            ~Node();
            double predict(double x1, double x2)const;
            double gini_impurity(Training_data const&)const;
            std::string to_string()const;
            Node* parent;
            Node* right;
            Node* left;
            Split* split;
             
            unsigned depth;
            double value;
        };
};

#endif
