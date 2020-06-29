/******************* MCC EXAMPLE ******************/
// Last update: 29/06/2020
//
// In this example we show how you can use easyDAG to
// build a more complex pipeline for the evaluation of
// the Matthews Correlation Coefficient (MCC).
// We create a series of function starting from the
// implementation provided in the "scorer" project
// (https://github.com/Nico-Curti/scorer).
// We start from two arrays of labels (true labels and
// predicted labels) and we create a pipeline including
// each required step for the evaluation of the MCC
// starting from the Confusion Matrix of the problem.
// Please see the "scorer" project for more details.
//
/***************************************************/

#include <set>
#include <cmath>
#include <vector>
#include <memory>
#include <numeric>
#include <iostream>
#include <algorithm>

#include <task.hpp>

int main ()
{

  const int Nlabels = 12;
  int Nclass;

  int * y_true = new int[Nlabels];
  y_true[0] = 2;  y_true[1] = 0;  y_true[2] = 2;  y_true[3] = 2;  y_true[4] = 0;   y_true[5] = 1;
  y_true[6] = 1;  y_true[7] = 2;  y_true[8] = 2;  y_true[9] = 0;  y_true[10] = 1;  y_true[11] = 2;

  int * y_pred = new int[Nlabels];
  y_pred[0] = 0;  y_pred[1] = 0;  y_pred[2] = 2;  y_pred[3] = 1;  y_pred[4] = 0;   y_pred[5] = 2;
  y_pred[6] = 1;  y_pred[7] = 0;  y_pred[8] = 2;  y_pred[9] = 0;  y_pred[10] = 2;  y_pred[11] = 2;


  auto get_classes = [&] (const int * lbl_true, const int * lbl_pred, const int & n_true, const int & n_pred)
  {
    std :: set < int > u1 (lbl_true, lbl_true + n_true);
    std :: set < int > u2 (lbl_pred, lbl_pred + n_pred);

    std :: vector < float > classes (u1.size() + u2.size());
    auto it = std :: set_union(u1.begin(), u1.end(), u2.begin(), u2.end(), classes.begin());
    classes.resize(it - classes.begin());

    Nclass = static_cast < int >(classes.size());

    float * res = new float[classes.size()];
    std :: move(classes.begin(), classes.end(), res);

    return res;
  };

  auto get_confusion_matrix = [] (const int * lbl_true, const int * lbl_pred, const int & n_lbl, const float * classes, const int & Nclass)
  {
    float * confusion_matrix = new float[Nclass * Nclass];

    std :: fill_n(confusion_matrix, Nclass * Nclass, 0.f);

    auto start = classes;
    auto end   = classes + Nclass;

    for (int i = 0; i < n_lbl; ++i)
    {
      const int i1 = std :: distance(start, std :: find(start, end, lbl_true[i]));
      const int i2 = std :: distance(start, std :: find(start, end, lbl_pred[i]));
      ++ confusion_matrix[i1 * Nclass + i2];
    }
    return confusion_matrix;
  };

  auto get_TP = [] (const float * confusion_matrix, const int & Nclass)
  {
    float * TP = new float[Nclass];

    for (int i = 0; i < Nclass; ++i)
      TP[i] = confusion_matrix[i * Nclass + i];

    return TP;
  };

  auto get_FN = [] (const float * confusion_matrix, const int & Nclass)
  {
    float * FN = new float[Nclass];

    for (int i = 0; i < Nclass; ++i)
    {
      const int N = i * Nclass;
      FN[i] = std :: accumulate(confusion_matrix + N, confusion_matrix + N + i, 0.f) +
              std :: accumulate(confusion_matrix + N + i + 1, confusion_matrix + N + Nclass, 0.f);
    }
    return FN;
  };

  auto get_FP = [] (const float * confusion_matrix, const int & Nclass)
  {
    float * FP = new float[Nclass];

    std :: fill_n(FP, Nclass, 0.f);

    for (int i = 0; i < Nclass; ++i)
      for (int j = 0; j < Nclass; ++j)
        FP[j] += (i != j) ? confusion_matrix[i * Nclass + j] : 0.f;

    return FP;
  };

  auto get_TOP = [] (const float * TP, const float * FP, const int & Nclass)
  {
    float * TOP = new float[Nclass];
    std :: transform(TP, TP + Nclass, FP, TOP, [](const float & tp, const float & fp){return tp + fp;});
    return TOP;
  };

  auto get_P = [] (const float * TP, const float * FN, const int & Nclass)
  {
    float * P = new float[Nclass];
    std :: transform(TP, TP + Nclass, FN, P, [](const float & tp, const float & fn){return tp + fn;});
    return P;
  };

  auto get_overall_MCC = [] (const float * confusion_matrix, const float * TOP, const float * P, const int & Nclass)
  {
    const float s = std :: accumulate(TOP, TOP + Nclass, 0.f);
    float cov_x_y = 0.f;
    float cov_x_x = 0.f;
    float cov_y_y = 0.f;

    for (int i = 0; i < Nclass; ++i)
    {
      cov_x_x += TOP[i] * (s - TOP[i]);
      cov_y_y += P[i] *   (s - P[i]);
      cov_x_y += confusion_matrix[i * Nclass + i] * s - P[i] * TOP[i];
    }

    return cov_x_y / std :: sqrt(cov_y_y * cov_x_x);
  };


  auto yt = InputVariable(y_true);
  yt.set_name(y_true);

  auto yp = InputVariable(y_pred);
  yp.set_name(y_pred);

  auto n_labels = InputVariable(Nlabels);
  n_labels.set_name(Nlabels);

  auto n_class = InputVariable < int >();
  n_class.set_name(Nclass);

  // Compute the unique classes
  Task classes(get_classes, yt, yp, n_labels, n_labels);
  classes.set_name(classes);

  // set the Nclass as step for printing
  classes();
  n_class.set(Nclass);

  // Compute the confusion matrix
  Task confusion_matrix(get_confusion_matrix, yt, yp, n_labels, classes, n_class);
  confusion_matrix.set_name(confusion_matrix);

  // Compute the True Positive
  Task TP(get_TP, confusion_matrix, n_class);
  TP.set_name(TP);
  // Compute the False Positive
  Task FP(get_FP, confusion_matrix, n_class);
  FP.set_name(FP);
  // Compute the False Negative
  Task FN(get_FN, confusion_matrix, n_class);
  FN.set_name(FN);

  // Compute the Test outcome positive
  Task TOP(get_TOP, TP, FP, n_class);
  TOP.set_name(TOP);
  // Compute the Condition positive or support
  Task P(get_P, TP, FN, n_class);
  P.set_name(P);

  // Compute the Matthews Correlation Coefficient
  Task MCC(get_overall_MCC, confusion_matrix, TOP, P, n_class);
  MCC.set_name(MCC);

  auto res = MCC();

  std :: cout << "Matthews Correlation Coefficient: " << res << std :: endl;

  std :: cout << std :: endl << "DOT graph:" << std :: endl;
  MCC.graphviz(std :: cout, "matthews_coefficient");

  return 0;
}
