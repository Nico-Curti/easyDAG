#include <set>
#include <cmath>
#include <vector>
#include <memory>
#include <numeric>
#include <iostream>
#include <algorithm>

#include <step.hpp>

int main ()
{

  const int Nlabels = 12;
  int Nclass;

  std :: shared_ptr < int[] > y_true(new int[Nlabels]);
  y_true[0] = 2;  y_true[1] = 0;  y_true[2] = 2;  y_true[3] = 2;  y_true[4] = 0;   y_true[5] = 1;
  y_true[6] = 1;  y_true[7] = 2;  y_true[8] = 2;  y_true[9] = 0;  y_true[10] = 1;  y_true[11] = 2;

  std :: shared_ptr < int[] > y_pred(new int[Nlabels]);
  y_pred[0] = 0;  y_pred[1] = 0;  y_pred[2] = 2;  y_pred[3] = 1;  y_pred[4] = 0;   y_pred[5] = 2;
  y_pred[6] = 1;  y_pred[7] = 0;  y_pred[8] = 2;  y_pred[9] = 0;  y_pred[10] = 2;  y_pred[11] = 2;


  auto get_classes = [&] (const std :: shared_ptr < int[] > & lbl_true, const std :: shared_ptr < int[] > & lbl_pred, const int & n_true, const int & n_pred)
  {
    std :: set < int > u1 (lbl_true.get(), lbl_true.get() + n_true);
    std :: set < int > u2 (lbl_pred.get(), lbl_pred.get() + n_pred);

    std :: vector < float > classes (u1.size() + u2.size());
    auto it = std :: set_union(u1.begin(), u1.end(), u2.begin(), u2.end(), classes.begin());
    classes.resize(it - classes.begin());

    std :: shared_ptr < float[] > res(new float[classes.size()]);
    std :: move(classes.begin(), classes.end(), res.get());

    return res;
  };

  auto get_confusion_matrix = [] (const std :: shared_ptr < int[] > & lbl_true, const std :: shared_ptr < int[] > & lbl_pred, const int & n_lbl, const std :: shared_ptr < float[] > & classes, const int & Nclass)
  {
    std :: shared_ptr < float[] > confusion_matrix(new float[Nclass * Nclass]);

    std :: fill_n(confusion_matrix.get(), Nclass * Nclass, 0.f);

    auto start = classes.get();
    auto end   = classes.get() + Nclass;

    int i1 = 0;
    int i2 = 0;

    for (int i = 0; i < n_lbl; ++i)
    {
      i1 = std :: distance(start, std :: find(start, end, lbl_true[i]));
      i2 = std :: distance(start, std :: find(start, end, lbl_pred[i]));
      ++ confusion_matrix[i1 * Nclass + i2];
    }
    return confusion_matrix;
  };

  auto get_TP = [] (const std :: shared_ptr < float[] > & confusion_matrix, const int & Nclass)
  {
    std :: shared_ptr < float[] > TP(new float[Nclass]);

    for (int i = 0; i < Nclass; ++i)
      TP[i] = confusion_matrix[i * Nclass + i];

    return TP;
  };

  auto get_FN = [] (const std :: shared_ptr < float[] > & confusion_matrix, const int & Nclass)
  {
    std :: shared_ptr < float[] > FN(new float[Nclass]);

    for (int i = 0; i < Nclass; ++i)
    {
      const int N = i * Nclass;
      FN[i] = std :: accumulate(confusion_matrix.get() + N, confusion_matrix.get() + N + i, 0.f) +
              std :: accumulate(confusion_matrix.get() + N + i + 1, confusion_matrix.get() + N + Nclass, 0.f);
    }
    return FN;
  };

  auto get_FP = [] (const std :: shared_ptr < float[] > & confusion_matrix, const int & Nclass)
  {
    std :: shared_ptr < float[] > FP(new float[Nclass]);

    std :: fill_n(FP.get(), Nclass, 0.f);

    for (int i = 0; i < Nclass; ++i)
      for (int j = 0; j < Nclass; ++j)
        FP[j] += (i != j) ? confusion_matrix[i * Nclass + j] : 0.f;

    return FP;
  };

  auto get_TOP = [] (const std :: shared_ptr < float[] > & TP, const std :: shared_ptr < float[] > & FP, const int & Nclass)
  {
    std :: shared_ptr < float[] > TOP (new float[Nclass]);
    std :: transform(TP.get(), TP.get() + Nclass, FP.get(), TOP.get(), [](const float & tp, const float & fp){return tp + fp;});
    return TOP;
  };

  auto get_P = [] (const std :: shared_ptr < float[] > & TP, const std :: shared_ptr < float[] > & FN, const int & Nclass)
  {
    std :: shared_ptr < float[] > P (new float[Nclass]);
    std :: transform(TP.get(), TP.get() + Nclass, FN.get(), P.get(), [](const float & tp, const float & fn){return tp + fn;});
    return P;
  };

  auto get_overall_MCC = [] (const std :: shared_ptr < float[] > & confusion_matrix, const std :: shared_ptr < float[] > & TOP, const std :: shared_ptr < float[] > & P, const int & Nclass)
  {
    const float s = std :: accumulate(TOP.get(), TOP.get() + Nclass, 0.f);
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
  Step classes(get_classes, yt, yp, n_labels, n_labels);
  classes.set_name(classes);

  // set the Nclass as step for printing
  n_class.set(Nclass);

  // Compute the confusion matrix
  Step confusion_matrix(get_confusion_matrix, yt, yp, n_labels, classes, n_class);
  confusion_matrix.set_name(confusion_matrix);

  // Compute the True Positive
  Step TP(get_TP, confusion_matrix, n_class);
  TP.set_name(TP);
  // Compute the False Positive
  Step FP(get_FP, confusion_matrix, n_class);
  FP.set_name(FP);
  // Compute the False Negative
  Step FN(get_FN, confusion_matrix, n_class);
  FN.set_name(FN);

  // Compute the Test outcome positive
  Step TOP(get_TOP, TP, FP, n_class);
  TOP.set_name(TOP);
  // Compute the Condition positive or support
  Step P(get_P, TP, FN, n_class);
  P.set_name(P);

  // Compute the Matthews Correlation Coefficient
  Step MCC(get_overall_MCC, confusion_matrix, TOP, P, n_class);
  MCC.set_name(MCC);

  auto res = MCC();

  std :: cout << "Matthews Correlation Coefficient: " << res << std :: endl;

  std :: cout << std :: endl << "DOT graph:" << std :: endl;
  MCC.graph(std :: cout, "matthews_coefficient");

  return 0;
}