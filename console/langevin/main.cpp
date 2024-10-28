

#include <kiam.hpp>
using namespace Kiam;
#include <base/time.hpp>
#include <base/user.hpp>
#include <base/marray.hpp>
#include <base/matrix.hpp>
#include <math/rnd.hpp>
#include <math/matrix2.hpp>
#include "extscene.hpp"
#include "lmcsolver.hpp"

#include <time.h>

double get_cpu_time()
{
    return (double)clock() / CLOCKS_PER_SEC;
}
















OKAY main2(int argc, const char **argv);
extern OKAY LangevinTest();
extern OKAY LangevinTest2(int argc, const char **argv);

extern OKAY ProcCmdLine(int argc, const char **argv,
                        OUT double &zf1,
                        OUT double &ecc1,
                        OUT double &zf2,
                        OUT double &ecc2,
                        OUT double &za,
                        OUT double &ra,
                        OUT double &cam_view_angle,
                        OUT double &gs1,
                        OUT double &gs2,
                        OUT double &dt,
                        OUT bool   &auto_dt_max,
                        OUT bool   &matrices,
                        OUT Str    &hastings,
                        OUT Str    &drift);






int main(int argc, const char **argv)
  {

  int ret = main2(argc, argv);

  return ret;
  }











OKAY main2(int argc, const char **argv)
  {
#if 1
  int rc = LangevinTest2(argc, argv);
#else
  int rc = LangevinTest();
#endif

  printf("Done\n");        
  return rc;
  }

OKAY LangevinTest2(int argc, const char **argv)
  {
  Rnd rng1(1234567890), rng2(1234567890);

  double zf1 = 1, ecc1 = 2, zf2 = 2, ecc2 = 2, za = zf1, ra = 0.025 /**30*/,
         cam_view_angle = Rad(45.0), gs1 = 100, gs2 = 100;
  const Vect3d ls_shift(0, 0, 0), cam_shift(0, 0, 0);

  LMCSolver::LMCOptions options;
  options.auto_dt_max = true;
  options.dt       = 0.01;
  options.drift    = LMCSolver::LMCOptions::DRIFT_FULL;
  options.hastings = LMCSolver::LMCOptions::HASTINGS_FULL;

  if (argc > 1)
    {
    Str hastings_str, drift_str;
    if (ProcCmdLine(argc, argv, zf1, ecc1, zf2, ecc2, za, ra, cam_view_angle, gs1, gs2,
      options.dt, options.auto_dt_max, options.matrices,
      hastings_str, drift_str) != SUCCESS)
      {
      printf("Can not retrieve options\n");
      Assert(false);
      return FAILURE;
      }

    if (drift_str.ICmp("full") == 0)
      options.drift = LMCSolver::LMCOptions::DRIFT_FULL;
    else if (drift_str.ICmp("grad") == 0)
      options.drift = LMCSolver::LMCOptions::DRIFT_GRAD;
    else if (drift_str.ICmp("div") == 0)
      options.drift = LMCSolver::LMCOptions::DRIFT_DIV;
    else if (drift_str.ICmp("none") == 0)
      options.drift = LMCSolver::LMCOptions::DRIFT_NONE;
    else
      {
      printf("Unknown drift mode %s\n", drift_str.Data());
      Assert(false);
      return FAILURE;
      }


    if (hastings_str.ICmp("full") == 0)
      options.hastings = LMCSolver::LMCOptions::HASTINGS_FULL;
    else if (hastings_str.ICmp("partial") == 0)
      options.hastings = LMCSolver::LMCOptions::HASTINGS_PARTIAL;
    else
      {
      printf("Unknown Hastings mode %s\n", hastings_str.Data());
      Assert(false);
      return FAILURE;
      }
    printf("Hastings = %i Drift = %i\n", options.hastings, options.drift);
    }

  ExtScene scene;
  if (scene.Create(zf1, ecc1, zf2, ecc2, za, ra, ls_shift, cam_shift, cam_view_angle,
                   gs1, gs2) != SUCCESS)
    {
    Assert(false);
    return FAILURE;
    }
  LMCSolver lmcsolver;
  lmcsolver.Create(&scene);

  lmcsolver.SetOptions(options);


  const int nx = 301, ny = 3, nrays = 1000000000/*0*/;
  TMatrix<double> hist0, hist, hist_v1;
  hist0.Allocate(nx, ny);
  hist.Allocate(nx, ny);
  hist_v1.Allocate(nx, ny);
  hist0 = 0;
  hist = 0;
  hist_v1 = 0;

#if 1
  double tol = 0.001 / 3;

  if (scene.CalcDistr(nrays/1000, hist0, tol, rng1) != SUCCESS)
    {
    Assert(false);
    return FAILURE;
    }
  char buf_rng1[Rnd::STRING_LEN];
  rng1.RndStore(buf_rng1);
  printf("rng1: %s\n\n", buf_rng1);

  FILE *fd0 = fopen("hist0.dat", "w");
  for (int ix = 0; ix < nx; ix++)
    {
    for (int iy = 0; iy < ny; iy++)
      fprintf(fd0, "%15.10f ", hist0(ix, iy));
    fprintf(fd0, "\n");
    }
  fclose(fd0);
#else
  char buf_rng1[Rnd::STRING_LEN] = "2613 495c 1f52";
  rng1 = Rnd(buf_rng1);
  printf("rng1: %s\n\n", buf_rng1);
#endif

  TArray<double> hist0_avr, hist_avr;
  hist0_avr.Allocate(hist0.NRows());
  hist_avr.Allocate(hist0.NRows());
  for (int i = 0; i < hist0.NRows(); i++)
    {
    double avr = 0;
    for (int j = 0; j < hist0.NColumns(); j++)
      avr += hist0(i, j);
    avr /= hist0.NColumns();

    hist0_avr[i] = avr;
    }
  fd0 = fopen("hist0_avr.dat", "w");
  for (int ix = 0; ix < nx; ix++)
    fprintf(fd0, "%15.10f\n", hist0_avr[ix]);
  fclose(fd0);



  LMCSolver::BasePathDataSpecDir bpd;
  LMCSolver::StepData sd;
  LMCSolver::FullPathData &fpd = sd.fpd;
  if (scene.GeneratePath(*((ExtScene::BasePathDataSpecDir *)(&bpd)), rng1) != SUCCESS)
    {
    Assert(false);
    return FAILURE;
    }

  hist = hist0;
  hist = 0;
  hist_v1 = hist0;
  hist_v1 = 0;

  hist_avr = hist0_avr;
  hist_avr = 0;
  INT64 iter, n_accepted = 0, n_large_div = 0;
  const INT64 niter = 10000000000;
  double div_max = 0, div_avr = 0, div_sqr_avr = 0, dt_actual;

  FILE *fd_out = fopen("langevin.out", "w");
  fprintf(fd_out, "zf1 = %10.5f ecc1 = %10.5f gs1 = %10.5f\n", zf1, ecc1, gs1);
  fprintf(fd_out, "zf2 = %10.5f ecc2 = %10.5f gs2 = %10.5f\n", zf2, ecc2, gs2);
  fprintf(fd_out, "za  = %10.5f   ra = %10.5f  dt = %10.5f\n", za, ra, options.dt);
  fprintf(fd_out, "cam_view_angle = %10.5f\n", Deg(cam_view_angle));
  fprintf(fd_out, "auto_dt_max = %s\n", options.auto_dt_max ? "yes" : "no");
  fprintf(fd_out, "matrices = %s\n", options.matrices ? "yes" : "no");
  fprintf(fd_out, "hastings = %s\n", options.hastings == LMCSolver::LMCOptions::HASTINGS_FULL ? "full" : "partial");

  if (options.drift == LMCSolver::LMCOptions::DRIFT_FULL)
    fprintf(fd_out, "drift    = full\n");
  else if (options.drift == LMCSolver::LMCOptions::DRIFT_NONE)
    fprintf(fd_out, "drift    = none\n");
  else if (options.drift == LMCSolver::LMCOptions::DRIFT_GRAD)
    fprintf(fd_out, "drift    = grad\n");
  else if (options.drift == LMCSolver::LMCOptions::DRIFT_DIV)
    fprintf(fd_out, "drift    = div\n");
  fprintf(fd_out, "--------------------------------------------------\n\n\n\n");

  fprintf(fd_out, "Rel. accuracy in the reference histogram = %10.5f\n\n\n\n", tol);

  FILE *fd_out1 = fopen("hist-dev.tsr", "w");

  double time_beg, time_end, time_tot = 0, t = 0;
  for (iter = 0; iter < niter; iter++)
    {
    time_beg = get_cpu_time();
    const bool accept = lmcsolver.DoOneStep(bpd, sd, dt_actual, rng1);
    t += dt_actual;
    time_end = get_cpu_time();
    time_tot += (time_end - time_beg);

    const double div_len = Sqrt(Sqr(sd.drift.x) + Sqr(sd.drift.y) + Sqr(sd.drift.z) + Sqr(sd.drift.w));
    div_max = Max(div_max, div_len);
    div_avr += div_len;
    div_sqr_avr += Sqr(div_len);
    n_large_div += (div_len > 20);


#if 1
    double theta = ACos(fpd.v3.z);
    double phi = ATan2(fpd.v3.y, fpd.v3.x);
    if (phi < 0)
      phi += 2 * PI;

    int itheta = int((theta / PI) * (nx - 1));
    int iphi = int((phi / PI2)  * (ny - 1));
    double theta1 = itheta * PI / (nx - 1);
    double theta2 = (itheta + 1) * PI / (nx - 1);
    double weight = 1 / (cos(theta1) - cos(theta2));

    hist(itheta, iphi) += weight;
    hist_avr[itheta] += weight;


    theta = ACos(fpd.v1.z);
    phi = ATan2(fpd.v1.y, fpd.v1.x);
    if (phi < 0)
      phi += 2 * PI;

    itheta = int((theta / PI) * (nx - 1));
    iphi = int((phi / PI2)  * (ny - 1));
    theta1 = itheta * PI / (nx - 1);
    theta2 = (itheta + 1) * PI / (nx - 1);
    weight = 1 / (cos(theta1) - cos(theta2));
    hist_v1(itheta, iphi) += 1 / (cos(theta1) - cos(theta2));
#else
    int ix = int(((fpd.v3.x + 1) / 2.0) * nx);
    int iy = int(((fpd.v3.y + 1) / 2.0) * ny);
    hist(ix, iy) += 1;
#endif
    n_accepted += accept;

    if ((iter % 100000) == 0)
      {
      
      
      double sum0 = 0, sum = 0, sum1 = 0;
      for (int i = 0; i < nx - 5; i++)
        {
        if (hist0_avr[i] * hist_avr[i] == 0)
          continue; 
        sum0 += hist0_avr[i] * hist0_avr[i];
        sum  += hist0_avr[i] * hist_avr[i];
        sum1 += hist_avr[i] * hist_avr[i];
        }
      const double c = sum / sum0;
      const double diff = Sqrt(fabs(sum1 + c * c * sum0 - 2 * c * sum) / sum1);


      printf("%12I64i (%8.2f%%) %8.5f %10.5f     %11.5f %11.5f %11.5f %12I64i     %10.2f sec\n", 
             iter, 100.0 * double(1 + iter) / double(niter), double(n_accepted) / (1 + iter), diff, 
             div_max, div_avr / (1 + iter), Sqrt(div_sqr_avr / (1 + iter)), n_large_div,
             time_tot);
      fprintf(fd_out, "%12I64i (%8.2f%%) %8.5f %10.5f     %11.5f %11.5f %11.5f %12I64i     %10.2f sec\n",
              iter, 100.0 * double(1 + iter) / double(niter), double(n_accepted) / (1 + iter), diff,
              div_max, div_avr / (1 + iter), Sqrt(div_sqr_avr / (1 + iter)), n_large_div,
              time_tot);

      fprintf(fd_out1, "%12I64i %20.4f %10.3f %10.5f\n", iter, t, time_tot, diff);

      fflush(fd_out);
      fflush(fd_out1);


      FILE *fd;
      fd = fopen("hist_avr.dat", "w");
      for (int ix = 0; ix < nx; ix++)
        fprintf(fd, "%10.5f %12.7f %12.7f\n", Deg(ix * PI / (nx - 1)), 
                hist_avr[ix] / c, hist0_avr[ix]);
      fclose(fd);

      fd = fopen("hist.dat", "w");
      for (int ix = 0; ix < nx; ix++)
        {
        for (int iy = 0; iy < ny; iy++)
          fprintf(fd, "%5.2f ", 1000*hist(ix, iy) / (iter + 1));
        fprintf(fd, "\n");
        }
      fclose(fd);

      fd = fopen("hist_v1.dat", "w");
      for (int ix = 0; ix < nx; ix++)
        {
        for (int iy = 0; iy < ny; iy++)
          fprintf(fd, "%5.2f ", 1000 * hist_v1(ix, iy) / (iter + 1));
        fprintf(fd, "\n");
        }
      fclose(fd);
      }
    }
  fclose(fd_out);

  return SUCCESS;
  }
