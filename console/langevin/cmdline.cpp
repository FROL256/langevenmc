








#include <kiam.hpp>
using namespace Kiam;

#include <base/str.hpp>
#include <base/base.hpp>
#include <math/math.hpp>



const static Str prefix("-");




const static Str suffix("=");

static bool GetIntParam(const char *word, const Str &keyword,
                        int low, int high, OUT int &value);
static bool GetFloatParam(const char *word, const Str &keyword,
                          double low, double high, OUT double &value);
static bool GetStrParam(const char *word, const Str &keyword, OUT Str &value);
static bool GetFileNameParam(const char *word, const Str &keyword,
                             OUT Str &fname);













OKAY ProcCmdLine(int argc, const char **argv,
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
                 OUT Str    &drift)
{
  
  zf1 = 1;
  ecc1 = 2; 
  zf2 = 2; 
  ecc2 = 2; 
  za = zf1; 
  ra = 0.025;
  cam_view_angle = Rad(45.0);
  gs1 = 100;
  gs2 = 100;
  dt = 0.01;
  auto_dt_max = true;
  matrices = true;
  hastings = "full";
  drift = "full";

  if (argc > 1 && (strcmp(argv[1], "-help") == 0 || strcmp(argv[1], "-?") == 0 || strcmp(argv[1], "-h") == 0))
  {
#if 0
    printf(
      "Postprocessor of diffraction results for pigmented layer.\n"
      "Version 1.02, Copyright (C) Kiam Inc. 2005-2012\n\n");
    printf("\n");
    printf("USAGE: sds2ink.exe [%sfromdir%sroot] [%sS[%spattern]] [%soutname%sfile] [[%salbedo%s###] | [%salbedofile%sfile]] [%simgsize%s###]\n\n",
           prefix, suffix, prefix, suffix, prefix, suffix, prefix, suffix, prefix, suffix, prefix, suffix);
    printf("where:\n");
    printf(" %sfromdir%sroot    - Pathname of start folder; '.' is for current dir\n", prefix, suffix);
    printf("                      Default = current\n");
    printf(" %sS               - search result files in all subfolders\n", prefix);
    printf(" %sS%spattern       - search all subfolders and take result files\n", prefix, suffix);
    printf("                      whose full path (from current) contains this pattern\n");
    printf("                      It may run across several paths e.g. 'balls\\100nm' but may not contain blanks\n");
    printf(" %soutname%sfile    - 'file' is BASE (path)name of files where\n", prefix, suffix);
    printf("                      to put results combining data from ALL subfolders processed\n");
    printf("                      There will be several files with the same base name but different extensions\n");
    printf("                      which depends on data in particular file. In case of single folder they are not created.\n");
    printf("                      Omitting option (DEFAULT) means no combined results\n");
    printf(" %salbedo%s###      - Albedo of substrate in range [0,1); the same for all wavelengths\n", prefix, suffix);
    printf("                      Default = %f\n", albedo0);
    printf("                      If used together with 'albedofile', gives MAXIMUM of spectrogram\n");
    printf(" %salbedofile%sfile - 'file' contains pathname to file with spectrogram of albedo of substrate\n", prefix, suffix);
    printf("                      If used together with 'albedo', the latter gives spectrogram maximum.\n");
    printf(" %simgsize%s###     - (### is a number) size of BRDF image, in pixel\n", prefix, suffix);
    printf("                      Default = %3i\n", imgsize);
    printf("                      Value < 1 means that no image will be created.\n");
    printf(" %snoambstrip       - if this flag is specified, left strip showing BDF under ambient light is omitted\n", prefix);
    printf(" %sphong%s###       - (Half)-width of Phong highlight, degrees\n", prefix, suffix);
    printf("                      Affects only .ddr and .sdr files; not image\n");
    printf("                      If <=0 then diffuse and specular components are saved separated.\n");
    printf("                      If > 0 then specular BRDF is not saved; instead it is converted into\n");
    printf("                             Phong highlight and saved is duffuse BRDF with it\n");
    printf("                      Default = 0 (no highlight)\n");
    printf(" %smaxangle%s###    - max. angle in BDF colour fringes, degrees\n", prefix, suffix);
    printf("                      Affects only BDF colour images\n");
    printf("                      Allowed range 0.01 thru 89.99 deg. Default = 60 degrees\n");
#endif
    return FAILURE;
  }

  double val;
  Str str;
  for (int i = 1; i < argc; i++)
    {
    if (GetStrParam(argv[i], "matrices", str))
      {
      if (str.ICmp("yes") == 0 || str.ICmp("true") == 0 || str.ICmp("use") == 0)
        {
        matrices = true;
        continue; 
        }
      else if (str.ICmp("no") == 0 || str.ICmp("false") == 0 || str.ICmp("nouse") == 0)
        {
        matrices = false;
        continue; 
        }
      }

    if (GetStrParam(argv[i], "auto_dt_max", str))
      {
      if (str.ICmp("yes") == 0 || str.ICmp("true") == 0 || str.ICmp("use") == 0)
        {
        auto_dt_max = true;
        continue; 
        }
      else if (str.ICmp("no") == 0 || str.ICmp("false") == 0 || str.ICmp("nouse") == 0)
        {
        auto_dt_max = false;
        continue; 
        }
      }

    if (GetStrParam(argv[i], "drift", str))
      {
      if (str.ICmp("full") == 0 || str.ICmp("grad") == 0 || str.ICmp("div") == 0 || str.ICmp("none") == 0)
        {
        drift = str;
        continue; 
        }
      }
    if (GetStrParam(argv[i], "hastings", str))
      {
      if (str.ICmp("full") == 0 || str.ICmp("partial") == 0)
        {
        hastings = str;
        continue; 
        }
      }

    if (GetFloatParam(argv[i], "zf1", 0, 10, val))
      {
      zf1 = val;
      continue; 
      }
    if (GetFloatParam(argv[i], "zf2", 0, 10, val))
      {
      zf2 = val;
      continue; 
      }
    if (GetFloatParam(argv[i], "ecc1", 0, 10, val))
      {
      ecc1 = val;
      continue; 
      }
    if (GetFloatParam(argv[i], "ecc2", 0, 10, val))
      {
      ecc2 = val;
      continue; 
      }
    if (GetFloatParam(argv[i], "za", 0, 10, val))
      {
      za = val;
      continue; 
      }
    if (GetFloatParam(argv[i], "ra", 0, 10, val))
      {
      ra = val;
      continue; 
      }
    if (GetFloatParam(argv[i], "cam_view_angle", 0, 180, val))
      {
      cam_view_angle = Rad(val);
      continue; 
      }
    if (GetFloatParam(argv[i], "gs1", 0, 1e7, val))
      {
      gs1 = val;
      continue; 
      }
    if (GetFloatParam(argv[i], "gs2", 0, 1e7, val))
      {
      gs2 = val;
      continue; 
      }
    if (GetFloatParam(argv[i], "dt", 0, 10, val))
      {
      dt = val;
      continue; 
      }

    printf("CMDLINE ERROR: Illegal option '%s'\n", argv[i]);
    printf("use '-?' or '-help' for list of options\n");
    return FAILURE;
  }

  printf("\n\n\n--------------------------------------------------\n");
  printf("Options in effect:\n");

  printf("zf1 = %10.5f ecc1 = %10.5f gs1 = %10.5f\n", zf1, ecc1, gs1);
  printf("zf2 = %10.5f ecc2 = %10.5f gs2 = %10.5f\n", zf2, ecc2, gs2);
  printf("za  = %10.5f   ra = %10.5f  dt = %10.5f\n", za, ra, dt);
  printf("cam_view_angle = %10.5f\n", Deg(cam_view_angle));
  printf("auto_dt_max = %s\n", auto_dt_max ? "yes" : "no");
  printf("matrices = %s\n", matrices ? "yes" : "no");
  printf("hastings = %s\n", hastings.Data());
  printf("drift    = %s\n", drift.Data());

  printf("--------------------------------------------------\n\n\n\n");
  return SUCCESS;
}
































bool GetStrParam(const char *word, const Str &keyword, OUT Str &value)
{
  Str keyword1 = prefix + keyword + suffix;

  if (strncmp(word, keyword1, keyword1.Length()) == 0)
  {
    value = word + keyword1.Length(); 
    return true;
  }
  return false;
}



































bool GetFloatParam(const char *word, const Str &keyword,
  double low, double high, OUT double &value)
  {
  Str keyword1 = prefix + keyword + suffix;

  if (strncmp(word, keyword1, keyword1.Length()) == 0)
    {
    const char *pc = word + keyword1.Length(); 
    double n = atof(pc);
    if (n >= low && n <= high)
      value = n;
    else
      printf("CMDLINE ERROR: Bad value of %s=%f; default %f used\n",
        keyword.Data(), n, value);
    return true;
    }
  return false;
  }

#if 0


































bool GetIntParam(const char *word, const Str &keyword,
                 int low, int high, OUT int &value)
{
  Str keyword1 = prefix + keyword + suffix;

  if (strncmp(word, keyword1, keyword1.Length()) == 0)
  {
    const char *pc = word + keyword1.Length(); 
    int n = atoi(pc);
    if (n >= low && n <= high)
      value = n;
    else
      printf("CMDLINE ERROR: Bad value of %s=%i; default %i used\n",
             keyword.Data(), n, value);
    return true;
  }
  return false;
}



































bool GetFileNameParam(const char *word, const Str &keyword, OUT Str &fname)
{
  Str keyword1 = prefix + keyword + suffix;

  if (strncmp(word, keyword1, keyword1.Length()) == 0)
  {
    Str valuestr = word + keyword1.Length(); 
    if (valuestr.IsFile())
      fname = valuestr;
    else
      printf("CMDLINE ERROR: Option %s%s points to illegal file; default %s used\n",
             keyword1.Data(), valuestr.Data(), fname.Data());
    return true;
  }
  return false;
}
#endif