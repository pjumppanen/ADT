//  ----------------------------------------------------------------------------
//  ADT generated file implementing class D_OperatingModelBase
//  ----------------------------------------------------------------------------

#include "Mseom.hpp"




#include "D_Mseom.hpp"



// ----------------------------------------------------------------------------

D_OperatingModelBase::D_OperatingModelBase(int arg_nsim, int arg_npop, int arg_nages, int arg_nsubyears, int arg_nareas, int arg_nfleets, const ARRAY_1I arg_Recsubyr)
 : OperatingModelBase(arg_nsim,arg_npop,arg_nages,arg_nsubyears,arg_nareas,arg_nfleets,arg_Recsubyr)
{
  create(fmd1_par,FM);
  create(movnd1_par,MovN);
  create(eforyeard1_par,EforYear);
  create(fmb2_par,FM);
  create(movnb2_par,MovN);
  create(eforyearb2_par,EforYear);
  createStack(i4stack_1_2);
  i4stack_1_2i = 0;
  createStack(r4stack_1_2);
  r4stack_1_2i = 0;
  createStack(i4stack_2_2);
  i4stack_2_2i = 0;
  createStack(i4stack_3_2);
  i4stack_3_2i = 0;
  createStack(r4stack_3_2);
  r4stack_3_2i = 0;
  createStack(bstack_3_2);
  bstack_3_2i = 0;
}
;

// ----------------------------------------------------------------------------

D_OperatingModelBase::D_OperatingModelBase(const D_OperatingModelBase& rCopy)
 : OperatingModelBase(rCopy)
{
  create(fmd1_par,FM);
  create(movnd1_par,MovN);
  create(eforyeard1_par,EforYear);
  create(fmb2_par,FM);
  create(movnb2_par,MovN);
  create(eforyearb2_par,EforYear);
  createStack(i4stack_1_2);
  i4stack_1_2i = 0;
  createStack(r4stack_1_2);
  r4stack_1_2i = 0;
  createStack(i4stack_2_2);
  i4stack_2_2i = 0;
  createStack(i4stack_3_2);
  i4stack_3_2i = 0;
  createStack(r4stack_3_2);
  r4stack_3_2i = 0;
  createStack(bstack_3_2);
  bstack_3_2i = 0;
}
;

// ----------------------------------------------------------------------------

D_OperatingModelBase::~D_OperatingModelBase()
{
  destroy(fmd1_par);
  destroy(movnd1_par);
  destroy(eforyeard1_par);
  destroy(fmb2_par);
  destroy(movnb2_par);
  destroy(eforyearb2_par);
  destroy(i4stack_1_2);
  destroy(r4stack_1_2);
  destroy(i4stack_2_2);
  destroy(i4stack_3_2);
  destroy(r4stack_3_2);
  destroy(bstack_3_2);
}

// ----------------------------------------------------------------------------

//   Differentiation of operatingmodelbase__msyrefs_objective in forward (tangent) mode:
//    variations   of useful results: operatingmodelbase__msyrefs_objective
//    with respect to varying inputs: par
//    RW status of diff variables: movn:(loc) fm:(loc) eforyear:(loc)
//                 nbefore:(loc) n:(loc) operatingmodelbase__msyrefs_objective:out
//                 par:in c:(loc)
double D_OperatingModelBase::MSYREFS_OBJECTIVE_DPAR(double par, double pard1_par, int nReport, const ARRAY_4D ECurrent/* nfleets,nareas,nsubyears,nsim */, const ARRAY_2D qy/* nfleets,nsim */, const ARRAY_2D R0/* npop,nsim */, const ARRAY_3D M/* nages,npop,nsim */, const ARRAY_3D mat/* nages,npop,nsim */, const ARRAY_4D Idist/* nareas,nages,npop,nsim */, const ARRAY_3D Len_age/* nages,npop,nsim */, const ARRAY_3D Wt_age/* nages,npop,nsim */, const ARRAY_3D sel/* nages,nfleets,nsim */, const ARRAY_6D mov/* nareas,nareas,nsubyears,nages,npop,nsim */, const ARRAY_2D h/* npop,nsim */, const ARRAY_3D Recdist/* nareas,npop,nsim */, const ARRAY_1I SRrel/* npop */, ARRAY_5D N/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nd1_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D NBefore/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nbefored1_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D SSN/* nareas,nsubyears,nages,npop,nsim */, ARRAY_6D C/* nfleets,nareas,nsubyears,nages,npop,nsim */, ARRAY_6D cd1_par/* nfleets,nareas,nsubyears,nages,npop,nsim */, ARRAY_2D SSBA/* npop,nsim */, int ntargets, const ARRAY_1I targpop/* ntargets */, int run_years, int sim_idx, double& MSYrefs_objective)
{
  int ca;
  int cf;
  int cm;
  int cp;
  int cr;
  double dCatch;
  double dcatchd1_par;
  double dObjective;
  double dobjectived1_par;
  int p;
  double ret_MSYREFS_OBJECTIVE_DPAR;
  POPDYN_MSY_PAR_DPAR(par,pard1_par,ECurrent,qy,R0,M,mat,Idist,Len_age,Wt_age,sel,mov,h,Recdist,SRrel,N,nd1_par,NBefore,nbefored1_par,SSN,C,cd1_par,SSBA,run_years,sim_idx);
  dCatch = 1.0e-6;
  cp = 1;
  dcatchd1_par = 0.0;
  
  while ((cp <= ntargets))
  {
    p = targpop[cp];
    cr = 1;
    
    while ((cr <= nareas))
    {
      ca = 1;
      
      while ((ca <= nages))
      {
        cf = 1;
        
        while ((cf <= nfleets))
        {
          cm = 1;
          
          while ((cm <= nsubyears))
          {
            dcatchd1_par = dcatchd1_par + Wt_age[ca][p][sim_idx] * cd1_par[cf][cr][cm][ca][p][sim_idx];
            dCatch = dCatch + C[cf][cr][cm][ca][p][sim_idx] * Wt_age[ca][p][sim_idx];
            cm = cm + 1;
          }
          
          cf = cf + 1;
        }
        
        ca = ca + 1;
      }
      
      cr = cr + 1;
    }
    
    cp = cp + 1;
  }
  
  dobjectived1_par = -(dcatchd1_par / dCatch);
  dObjective = -log(dCatch);
  ret_MSYREFS_OBJECTIVE_DPAR = dobjectived1_par;
  MSYrefs_objective = dObjective;
  return (ret_MSYREFS_OBJECTIVE_DPAR);
}

// ----------------------------------------------------------------------------

//   Differentiation of operatingmodelbase__popdyn_msy_par in forward (tangent) mode:
//    variations   of useful results: c
//    with respect to varying inputs: par
void D_OperatingModelBase::POPDYN_MSY_PAR_DPAR(double par, double pard1_par, const ARRAY_4D ECurrent/* nfleets,nareas,nsubyears,nsim */, const ARRAY_2D qy/* nfleets,nsim */, const ARRAY_2D R0/* npop,nsim */, const ARRAY_3D M/* nages,npop,nsim */, const ARRAY_3D mat/* nages,npop,nsim */, const ARRAY_4D Idist/* nareas,nages,npop,nsim */, const ARRAY_3D Len_age/* nages,npop,nsim */, const ARRAY_3D Wt_age/* nages,npop,nsim */, const ARRAY_3D sel/* nages,nfleets,nsim */, const ARRAY_6D mov/* nareas,nareas,nsubyears,nages,npop,nsim */, const ARRAY_2D h/* npop,nsim */, const ARRAY_3D Recdist/* nareas,npop,nsim */, const ARRAY_1I SRrel/* npop */, ARRAY_5D N/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nd1_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D NBefore/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nbefored1_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D SSN/* nareas,nsubyears,nages,npop,nsim */, ARRAY_6D C/* nfleets,nareas,nsubyears,nages,npop,nsim */, ARRAY_6D cd1_par/* nfleets,nareas,nsubyears,nages,npop,nsim */, ARRAY_2D SSBA/* npop,nsim */, int run_years, int sim_idx)
{
  int cf;
  int cr;
  int cs;
  int cy;
  int ix_0___;
  int ix_1___;
  int ix_2___;
  int ix_3___;
  int ix_4___;
  int ix_5___;
  double totF;
  double totfd1_par;
  totfd1_par = pard1_par * exp(par);
  totF = exp(par);
  popdyn_init(R0,mat,Idist,N,NBefore,SSN,sim_idx);
  cf = 1;
  
  for (ix_3___ = 1;ix_3___ <= nsim; ++ix_3___)
  {
    for (ix_2___ = 1;ix_2___ <= nsubyears; ++ix_2___)
    {
      for (ix_1___ = 1;ix_1___ <= nareas; ++ix_1___)
      {
        for (ix_0___ = 1;ix_0___ <= nfleets; ++ix_0___)
        {
          eforyeard1_par[ix_0___][ix_1___][ix_2___][ix_3___] = 0.0;
        }
      }
    }
  }
  
  while ((cf <= nfleets))
  {
    cr = 1;
    
    while ((cr <= nareas))
    {
      cs = 1;
      
      while ((cs <= nsubyears))
      {
        eforyeard1_par[cf][cr][cs][sim_idx] = ECurrent[cf][cr][cs][sim_idx] * totfd1_par;
        EforYear[cf][cr][cs][sim_idx] = totF * ECurrent[cf][cr][cs][sim_idx];
        cs = cs + 1;
      }
      
      cr = cr + 1;
    }
    
    cf = cf + 1;
  }
  
  cy = 1;
  
  for (ix_1___ = 1;ix_1___ <= nsim; ++ix_1___)
  {
    for (ix_0___ = 1;ix_0___ <= nareas; ++ix_0___)
    {
      movnd1_par[ix_0___][ix_1___] = 0.0;
    }
  }
  
  for (ix_1___ = 1;ix_1___ <= nsim; ++ix_1___)
  {
    for (ix_0___ = 1;ix_0___ <= nfleets; ++ix_0___)
    {
      fmd1_par[ix_0___][ix_1___] = 0.0;
    }
  }
  
  for (ix_4___ = 1;ix_4___ <= nsim; ++ix_4___)
  {
    for (ix_3___ = 1;ix_3___ <= npop; ++ix_3___)
    {
      for (ix_2___ = 1;ix_2___ <= nages; ++ix_2___)
      {
        for (ix_1___ = 1;ix_1___ <= nsubyears + 1; ++ix_1___)
        {
          for (ix_0___ = 1;ix_0___ <= nareas; ++ix_0___)
          {
            nbefored1_par[ix_0___][ix_1___][ix_2___][ix_3___][ix_4___] = 0.0;
          }
        }
      }
    }
  }
  
  for (ix_4___ = 1;ix_4___ <= nsim; ++ix_4___)
  {
    for (ix_3___ = 1;ix_3___ <= npop; ++ix_3___)
    {
      for (ix_2___ = 1;ix_2___ <= nages; ++ix_2___)
      {
        for (ix_1___ = 1;ix_1___ <= nsubyears + 1; ++ix_1___)
        {
          for (ix_0___ = 1;ix_0___ <= nareas; ++ix_0___)
          {
            nd1_par[ix_0___][ix_1___][ix_2___][ix_3___][ix_4___] = 0.0;
          }
        }
      }
    }
  }
  
  for (ix_5___ = 1;ix_5___ <= nsim; ++ix_5___)
  {
    for (ix_4___ = 1;ix_4___ <= npop; ++ix_4___)
    {
      for (ix_3___ = 1;ix_3___ <= nages; ++ix_3___)
      {
        for (ix_2___ = 1;ix_2___ <= nsubyears; ++ix_2___)
        {
          for (ix_1___ = 1;ix_1___ <= nareas; ++ix_1___)
          {
            for (ix_0___ = 1;ix_0___ <= nfleets; ++ix_0___)
            {
              cd1_par[ix_0___][ix_1___][ix_2___][ix_3___][ix_4___][ix_5___] = 0.0;
            }
          }
        }
      }
    }
  }
  
  while ((cy < run_years))
  {
    POPDYN_YEAR_DPAR(qy,R0,M,mat,Len_age,Wt_age,sel,EforYear,eforyeard1_par,mov,h,Recdist,MSY_Recdevs,MSY_RecSpatialDevs,SRrel,N,nd1_par,NBefore,nbefored1_par,SSN,C,cd1_par,SSBA,0,sim_idx);
    POPDYN_NEXT_YEAR_DPAR(N,nd1_par,NBefore,nbefored1_par,sim_idx);
    cy = cy + 1;
  }
  
  POPDYN_YEAR_DPAR(qy,R0,M,mat,Len_age,Wt_age,sel,EforYear,eforyeard1_par,mov,h,Recdist,MSY_Recdevs,MSY_RecSpatialDevs,SRrel,N,nd1_par,NBefore,nbefored1_par,SSN,C,cd1_par,SSBA,0,sim_idx);
}

// ----------------------------------------------------------------------------

//   Differentiation of operatingmodelbase__popdyn_next_year in forward (tangent) mode:
//    variations   of useful results: nbefore n
//    with respect to varying inputs: nbefore n
void D_OperatingModelBase::POPDYN_NEXT_YEAR_DPAR(ARRAY_5D N/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nd1_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D NBefore/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nbefored1_par/* nareas,nsubyears + 1,nages,npop,nsim */, int sim_idx)
{
  int ca;
  int cp;
  int cr;
  cr = 1;
  
  while ((cr <= nareas))
  {
    ca = 1;
    
    while ((ca <= nages))
    {
      cp = 1;
      
      while ((cp <= npop))
      {
        nd1_par[cr][1][ca][cp][sim_idx] = nd1_par[cr][nsubyears + 1][ca][cp][sim_idx];
        N[cr][1][ca][cp][sim_idx] = N[cr][nsubyears + 1][ca][cp][sim_idx];
        nbefored1_par[cr][1][ca][cp][sim_idx] = nbefored1_par[cr][nsubyears + 1][ca][cp][sim_idx];
        NBefore[cr][1][ca][cp][sim_idx] = NBefore[cr][nsubyears + 1][ca][cp][sim_idx];
        cp = cp + 1;
      }
      
      ca = ca + 1;
    }
    
    cr = cr + 1;
  }
}

// ----------------------------------------------------------------------------

//   Differentiation of operatingmodelbase__popdyn_year in forward (tangent) mode:
//    variations   of useful results: movn fm nbefore n c
//    with respect to varying inputs: movn fm nbefore n eannual c
void D_OperatingModelBase::POPDYN_YEAR_DPAR(const ARRAY_2D qy/* nfleets,nsim */, const ARRAY_2D R0/* npop,nsim */, const ARRAY_3D M/* nages,npop,nsim */, const ARRAY_3D mat/* nages,npop,nsim */, const ARRAY_3D Len_age/* nages,npop,nsim */, const ARRAY_3D Wt_age/* nages,npop,nsim */, const ARRAY_3D sel/* nages,nfleets,nsim */, const ARRAY_4D Eannual/* nfleets,nareas,nsubyears,nsim */, const ARRAY_4D eannuald1_par/* nfleets,nareas,nsubyears,nsim */, const ARRAY_6D mov/* nareas,nareas,nsubyears,nages,npop,nsim */, const ARRAY_2D h/* npop,nsim */, const ARRAY_3D Recdist/* nareas,npop,nsim */, const ARRAY_3D Recdevs/* SpawnPerYr,npop,nsim */, const ARRAY_3D RecSpatialDevs/* nareas,npop,nsim */, const ARRAY_1I SRrel/* npop */, ARRAY_5D N/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nd1_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D NBefore/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nbefored1_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D SSN/* nareas,nsubyears,nages,npop,nsim */, ARRAY_6D C/* nfleets,nareas,nsubyears,nages,npop,nsim */, ARRAY_6D cd1_par/* nfleets,nareas,nsubyears,nages,npop,nsim */, ARRAY_2D SSBA/* npop,nsim */, int bIgnoreLast, int sim_idx)
{
  int ca;
  int cf;
  int cp;
  int cr;
  int cr2;
  int cs;
  double dFM;
  double dfmd1_par;
  double dFtot;
  double dftotd1_par;
  double dN;
  double dnd1_par;
  double dPlusGroup;
  double dplusgroupd1_par;
  double dRecruitment;
  double drecruitmentd1_par;
  double dSSB;
  double dSSB_area;
  double dssb_aread1_par;
  double dssbd1_par;
  double dSSN;
  double dssnd1_par;
  double dZ;
  double dzd1_par;
  int nRecdevIdx;
  nRecdevIdx = 1;
  cs = 1;
  
  while ((cs <= nsubyears))
  {
    cp = 1;
    
    while ((cp <= npop))
    {
      dSSB = 0.0;
      cr = 1;
      dssbd1_par = 0.0;
      
      while ((cr <= nareas))
      {
        dSSB_area = 0.0;
        ca = 1;
        dssb_aread1_par = 0.0;
        
        while ((ca <= nages))
        {
          dssnd1_par = mat[ca][cp][sim_idx] * nbefored1_par[cr][cs][ca][cp][sim_idx];
          dSSN = NBefore[cr][cs][ca][cp][sim_idx] * mat[ca][cp][sim_idx];
          SSN[cr][cs][ca][cp][sim_idx] = dSSN;
          dssb_aread1_par = dssb_aread1_par + Wt_age[ca][cp][sim_idx] * dssnd1_par;
          dSSB_area = dSSB_area + dSSN * Wt_age[ca][cp][sim_idx];
          ca = ca + 1;
        }
        
        dssbd1_par = dssbd1_par + dssb_aread1_par;
        dSSB = dSSB + dSSB_area;
        cr = cr + 1;
      }
      
      SSBA[cp][sim_idx] = dSSB;
      
      if ((Recsubyr[cs] != 0))
      {
        if ((SRrel[cp] == 1))
        {
          drecruitmentd1_par = Recdevs[nRecdevIdx][cp][sim_idx] * (0.8 * R0[cp][sim_idx] * h[cp][sim_idx] * dssbd1_par * (0.2 * SSBpR[cp][sim_idx] * R0[cp][sim_idx] * (1.0 - h[cp][sim_idx]) + (h[cp][sim_idx] - 0.2) * dSSB) - 0.8 * R0[cp][sim_idx] * h[cp][sim_idx] * dSSB * (h[cp][sim_idx] - 0.2) * dssbd1_par) / pow((0.2 * SSBpR[cp][sim_idx] * R0[cp][sim_idx] * (1.0 - h[cp][sim_idx]) + (h[cp][sim_idx] - 0.2) * dSSB),2);
          dRecruitment = Recdevs[nRecdevIdx][cp][sim_idx] * (0.8 * R0[cp][sim_idx] * h[cp][sim_idx] * dSSB / (0.2 * SSBpR[cp][sim_idx] * R0[cp][sim_idx] * (1.0 - h[cp][sim_idx]) + (h[cp][sim_idx] - 0.2) * dSSB));
        }
        else
        {
          drecruitmentd1_par = Recdevs[nRecdevIdx][cp][sim_idx] * aR[cp][sim_idx] * (dssbd1_par * exp(-(bR[cp][sim_idx] * dSSB)) - dSSB * bR[cp][sim_idx] * dssbd1_par * exp(-(bR[cp][sim_idx] * dSSB)));
          dRecruitment = Recdevs[nRecdevIdx][cp][sim_idx] * aR[cp][sim_idx] * dSSB * exp(-(bR[cp][sim_idx] * dSSB));
        }
        
        cr = 1;
        
        while ((cr <= nareas))
        {
          nbefored1_par[cr][cs][1][cp][sim_idx] = RecSpatialDevs[cr][cp][sim_idx] * Recdist[cr][cp][sim_idx] * drecruitmentd1_par;
          NBefore[cr][cs][1][cp][sim_idx] = dRecruitment * RecSpatialDevs[cr][cp][sim_idx] * Recdist[cr][cp][sim_idx];
          nd1_par[cr][cs][1][cp][sim_idx] = nbefored1_par[cr][cs][1][cp][sim_idx];
          N[cr][cs][1][cp][sim_idx] = NBefore[cr][cs][1][cp][sim_idx];
          cr = cr + 1;
        }
      }
      
      ca = 1;
      
      while ((ca <= nages))
      {
        cr = 1;
        
        while ((cr <= nareas))
        {
          dN = 0.0;
          cr2 = 1;
          dnd1_par = 0.0;
          
          while ((cr2 <= nareas))
          {
            dnd1_par = dnd1_par + mov[cr][cr2][cs][ca][cp][sim_idx] * nd1_par[cr2][cs][ca][cp][sim_idx];
            dN = dN + N[cr2][cs][ca][cp][sim_idx] * mov[cr][cr2][cs][ca][cp][sim_idx];
            cr2 = cr2 + 1;
          }
          
          movnd1_par[cr][sim_idx] = dnd1_par;
          MovN[cr][sim_idx] = dN;
          cr = cr + 1;
        }
        
        cr = 1;
        
        while ((cr <= nareas))
        {
          nd1_par[cr][cs][ca][cp][sim_idx] = movnd1_par[cr][sim_idx];
          N[cr][cs][ca][cp][sim_idx] = MovN[cr][sim_idx];
          cr = cr + 1;
        }
        
        ca = ca + 1;
      }
      
      ca = 1;
      
      while ((ca <= nages))
      {
        cr = 1;
        
        while ((cr <= nareas))
        {
          dFtot = 0.0;
          cf = 1;
          dftotd1_par = 0.0;
          
          while ((cf <= nfleets))
          {
            dfmd1_par = sel[ca][cf][sim_idx] * qy[cf][sim_idx] * eannuald1_par[cf][cr][cs][sim_idx];
            dFM = Eannual[cf][cr][cs][sim_idx] * sel[ca][cf][sim_idx] * qy[cf][sim_idx];
            fmd1_par[cf][sim_idx] = dfmd1_par;
            FM[cf][sim_idx] = dFM;
            dftotd1_par = dftotd1_par + dfmd1_par;
            dFtot = dFtot + dFM;
            cf = cf + 1;
          }
          
          dzd1_par = dftotd1_par;
          dZ = dFtot + M[ca][cp][sim_idx] / nsubyears;
          cf = 1;
          
          while ((cf <= nfleets))
          {
            cd1_par[cf][cr][cs][ca][cp][sim_idx] = (nd1_par[cr][cs][ca][cp][sim_idx] * FM[cf][sim_idx] / dZ + N[cr][cs][ca][cp][sim_idx] * (fmd1_par[cf][sim_idx] * dZ - FM[cf][sim_idx] * dzd1_par) / pow(dZ,2)) * (1 - exp(-dZ)) + N[cr][cs][ca][cp][sim_idx] * FM[cf][sim_idx] * dzd1_par * exp(-dZ) / dZ;
            C[cf][cr][cs][ca][cp][sim_idx] = N[cr][cs][ca][cp][sim_idx] * (1 - exp(-dZ)) * (FM[cf][sim_idx] / dZ);
            cf = cf + 1;
          }
          
          nd1_par[cr][cs][ca][cp][sim_idx] = nd1_par[cr][cs][ca][cp][sim_idx] * exp(-dZ) - N[cr][cs][ca][cp][sim_idx] * dzd1_par * exp(-dZ);
          N[cr][cs][ca][cp][sim_idx] = N[cr][cs][ca][cp][sim_idx] * exp(-dZ);
          cr = cr + 1;
        }
        
        ca = ca + 1;
      }
      
      if ((cs != nsubyears) || (bIgnoreLast == 0))
      {
        cr = 1;
        
        while ((cr <= nareas))
        {
          dplusgroupd1_par = nd1_par[cr][cs][nages][cp][sim_idx];
          dPlusGroup = N[cr][cs][nages][cp][sim_idx];
          nbefored1_par[cr][cs + 1][1][cp][sim_idx] = 0.0;
          NBefore[cr][cs + 1][1][cp][sim_idx] = 0.0;
          nd1_par[cr][cs + 1][1][cp][sim_idx] = 0.0;
          N[cr][cs + 1][1][cp][sim_idx] = 0.0;
          ca = nages - 1;
          
          while ((ca >= 1))
          {
            nbefored1_par[cr][cs + 1][ca + 1][cp][sim_idx] = nd1_par[cr][cs][ca][cp][sim_idx];
            NBefore[cr][cs + 1][ca + 1][cp][sim_idx] = N[cr][cs][ca][cp][sim_idx];
            nd1_par[cr][cs + 1][ca + 1][cp][sim_idx] = nbefored1_par[cr][cs + 1][ca + 1][cp][sim_idx];
            N[cr][cs + 1][ca + 1][cp][sim_idx] = NBefore[cr][cs + 1][ca + 1][cp][sim_idx];
            ca = ca - 1;
          }
          
          nbefored1_par[cr][cs + 1][nages][cp][sim_idx] = nbefored1_par[cr][cs + 1][nages][cp][sim_idx] + dplusgroupd1_par;
          NBefore[cr][cs + 1][nages][cp][sim_idx] = NBefore[cr][cs + 1][nages][cp][sim_idx] + dPlusGroup;
          nd1_par[cr][cs + 1][nages][cp][sim_idx] = nd1_par[cr][cs + 1][nages][cp][sim_idx] + dplusgroupd1_par;
          N[cr][cs + 1][nages][cp][sim_idx] = N[cr][cs + 1][nages][cp][sim_idx] + dPlusGroup;
          cr = cr + 1;
        }
      }
      
      cp = cp + 1;
    }
    
    if ((Recsubyr[cs] != 0))
    {
      nRecdevIdx = nRecdevIdx + 1;
    }
    
    cs = cs + 1;
  }
}

// ----------------------------------------------------------------------------

//   Differentiation of operatingmodelbase__popdyn_projection_objective in reverse (adjoint) mode:
//    gradient     of useful results: operatingmodelbase__popdyn_projection_objective
//    with respect to varying inputs: par
//    RW status of diff variables: movn:(loc) fm:(loc) eforyear:(loc)
//                 nbefore:(loc) n:(loc) operatingmodelbase__popdyn_projection_objective:in-killed
//                 par:out c:(loc)
void D_OperatingModelBase::POPDYN_PROJECTION_OBJECTIVE_BPAR(const ARRAY_1D par/* 0:npar - 1 */, ARRAY_1D parb2_par/* 0:npar - 1 */, int npar, int nfixed, const ARRAY_1D TAC/* 0:npar - 1 */, const ARRAY_1D TAE/* 0:nfixed - 1 */, const ARRAY_1I FbyPar/* 0:npar - 1 */, const ARRAY_1I FbyFixed/* 0:nfixed - 1 */, const ARRAY_4D ECurrent/* nfleets,nareas,nsubyears,nsim */, const ARRAY_2D qy/* nfleets,nsim */, const ARRAY_2D R0/* npop,nsim */, const ARRAY_3D M/* nages,npop,nsim */, const ARRAY_3D mat/* nages,npop,nsim */, const ARRAY_4D Idist/* nareas,nages,npop,nsim */, const ARRAY_3D Len_age/* nages,npop,nsim */, const ARRAY_3D Wt_age/* nages,npop,nsim */, const ARRAY_3D Wt_age_mid/* nages,npop,nsim */, const ARRAY_3D sel/* nages,nfleets,nsim */, const ARRAY_6D mov/* nareas,nareas,nsubyears,nages,npop,nsim */, const ARRAY_2D h/* npop,nsim */, const ARRAY_3D Recdist/* nareas,npop,nsim */, const ARRAY_3D Recdevs/* SpawnPerYr,npop,nsim */, const ARRAY_3D RecSpatialDevs/* nareas,npop,nsim */, const ARRAY_1I SRrel/* npop */, ARRAY_5D N/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nb2_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D NBefore/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nbeforeb2_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D SSN/* nareas,nsubyears,nages,npop,nsim */, ARRAY_6D C/* nfleets,nareas,nsubyears,nages,npop,nsim */, ARRAY_6D cb2_par/* nfleets,nareas,nsubyears,nages,npop,nsim */, ARRAY_2D SSBA/* npop,nsim */, int sim_idx, double& popdyn_projection_objectiveb2_par)
{
  int ad_count;
  int ad_count0;
  int ad_count1;
  int ad_count2;
  int ad_count3;
  int ca;
  int cf;
  int cp;
  int cr;
  int cs;
  int cx;
  double dCatchBiomass;
  double dcatchbiomassb2_par;
  double dobjectiveb2_par;
  double dTACError;
  double dtacerrorb2_par;
  int i;
  int i0;
  int i1;
  int i2;
  int i3;
  int ix_0___;
  int ix_1___;
  int ix_2___;
  int ix_3___;
  int ix_4___;
  int ix_5___;
  double temp;
  cf = 0;
  dTACError = 0;
  dCatchBiomass = 0;
  popdyn_projection_par(par,npar,nfixed,TAE,FbyPar,FbyFixed,ECurrent,qy,R0,M,mat,Idist,Len_age,Wt_age,sel,mov,h,Recdist,Recdevs,RecSpatialDevs,SRrel,N,NBefore,SSN,C,SSBA,1,sim_idx);
  cx = 0;
  ad_count3 = 0;
  
  while ((cx < npar))
  {
    r4stack_1_2i = r4stack_1_2i + 1;
    
    if (r4stack_1_2i > stackSizeInt(r4stack_1_2))
    {
      growStack(r4stack_1_2,r4stack_1_2i);
    }
    
    r4stack_1_2[r4stack_1_2i] = dCatchBiomass;
    dCatchBiomass = 1.0e-6;
    i4stack_1_2i = i4stack_1_2i + 1;
    
    if (i4stack_1_2i > stackSizeInt(i4stack_1_2))
    {
      growStack(i4stack_1_2,i4stack_1_2i);
    }
    
    i4stack_1_2[i4stack_1_2i] = cf;
    cf = FbyPar[cx];
    cr = 1;
    ad_count2 = 0;
    
    while ((cr <= nareas))
    {
      ca = 1;
      ad_count1 = 0;
      
      while ((ca <= nages))
      {
        cp = 1;
        ad_count0 = 0;
        
        while ((cp <= npop))
        {
          cs = 1;
          ad_count = 0;
          
          while ((cs <= nsubyears))
          {
            dCatchBiomass = dCatchBiomass + C[cf][cr][cs][ca][cp][sim_idx] * Wt_age_mid[ca][cp][sim_idx];
            i4stack_1_2i = i4stack_1_2i + 1;
            
            if (i4stack_1_2i > stackSizeInt(i4stack_1_2))
            {
              growStack(i4stack_1_2,i4stack_1_2i);
            }
            
            i4stack_1_2[i4stack_1_2i] = cs;
            cs = cs + 1;
            ad_count = ad_count + 1;
          }
          
          i4stack_1_2i = i4stack_1_2i + 1;
          
          if (i4stack_1_2i > stackSizeInt(i4stack_1_2))
          {
            growStack(i4stack_1_2,i4stack_1_2i);
          }
          
          i4stack_1_2[i4stack_1_2i] = ad_count;
          i4stack_1_2i = i4stack_1_2i + 1;
          
          if (i4stack_1_2i > stackSizeInt(i4stack_1_2))
          {
            growStack(i4stack_1_2,i4stack_1_2i);
          }
          
          i4stack_1_2[i4stack_1_2i] = cp;
          cp = cp + 1;
          ad_count0 = ad_count0 + 1;
        }
        
        i4stack_1_2i = i4stack_1_2i + 1;
        
        if (i4stack_1_2i > stackSizeInt(i4stack_1_2))
        {
          growStack(i4stack_1_2,i4stack_1_2i);
        }
        
        i4stack_1_2[i4stack_1_2i] = ad_count0;
        i4stack_1_2i = i4stack_1_2i + 1;
        
        if (i4stack_1_2i > stackSizeInt(i4stack_1_2))
        {
          growStack(i4stack_1_2,i4stack_1_2i);
        }
        
        i4stack_1_2[i4stack_1_2i] = ca;
        ca = ca + 1;
        ad_count1 = ad_count1 + 1;
      }
      
      i4stack_1_2i = i4stack_1_2i + 1;
      
      if (i4stack_1_2i > stackSizeInt(i4stack_1_2))
      {
        growStack(i4stack_1_2,i4stack_1_2i);
      }
      
      i4stack_1_2[i4stack_1_2i] = ad_count1;
      i4stack_1_2i = i4stack_1_2i + 1;
      
      if (i4stack_1_2i > stackSizeInt(i4stack_1_2))
      {
        growStack(i4stack_1_2,i4stack_1_2i);
      }
      
      i4stack_1_2[i4stack_1_2i] = cr;
      cr = cr + 1;
      ad_count2 = ad_count2 + 1;
    }
    
    i4stack_1_2i = i4stack_1_2i + 1;
    
    if (i4stack_1_2i > stackSizeInt(i4stack_1_2))
    {
      growStack(i4stack_1_2,i4stack_1_2i);
    }
    
    i4stack_1_2[i4stack_1_2i] = ad_count2;
    r4stack_1_2i = r4stack_1_2i + 1;
    
    if (r4stack_1_2i > stackSizeInt(r4stack_1_2))
    {
      growStack(r4stack_1_2,r4stack_1_2i);
    }
    
    r4stack_1_2[r4stack_1_2i] = dTACError;
    dTACError = log(TAC[cx] / dCatchBiomass);
    i4stack_1_2i = i4stack_1_2i + 1;
    
    if (i4stack_1_2i > stackSizeInt(i4stack_1_2))
    {
      growStack(i4stack_1_2,i4stack_1_2i);
    }
    
    i4stack_1_2[i4stack_1_2i] = cx;
    cx = cx + 1;
    ad_count3 = ad_count3 + 1;
  }
  
  i4stack_1_2i = i4stack_1_2i + 1;
  
  if (i4stack_1_2i > stackSizeInt(i4stack_1_2))
  {
    growStack(i4stack_1_2,i4stack_1_2i);
  }
  
  i4stack_1_2[i4stack_1_2i] = ad_count3;
  dobjectiveb2_par = popdyn_projection_objectiveb2_par;
  
  for (ix_5___ = 1;ix_5___ <= nsim; ++ix_5___)
  {
    for (ix_4___ = 1;ix_4___ <= npop; ++ix_4___)
    {
      for (ix_3___ = 1;ix_3___ <= nages; ++ix_3___)
      {
        for (ix_2___ = 1;ix_2___ <= nsubyears; ++ix_2___)
        {
          for (ix_1___ = 1;ix_1___ <= nareas; ++ix_1___)
          {
            for (ix_0___ = 1;ix_0___ <= nfleets; ++ix_0___)
            {
              cb2_par[ix_0___][ix_1___][ix_2___][ix_3___][ix_4___][ix_5___] = 0.0;
            }
          }
        }
      }
    }
  }
  
  ad_count3 = i4stack_1_2[i4stack_1_2i];
  i4stack_1_2i = i4stack_1_2i - 1;
  
  for (i3 = 1;i3 <= ad_count3; ++i3)
  {
    cx = i4stack_1_2[i4stack_1_2i];
    i4stack_1_2i = i4stack_1_2i - 1;
    dtacerrorb2_par = 2 * dTACError * dobjectiveb2_par;
    dTACError = r4stack_1_2[r4stack_1_2i];
    r4stack_1_2i = r4stack_1_2i - 1;
    temp = TAC[cx] / dCatchBiomass;
    dcatchbiomassb2_par = -(dtacerrorb2_par / dCatchBiomass);
    ad_count2 = i4stack_1_2[i4stack_1_2i];
    i4stack_1_2i = i4stack_1_2i - 1;
    
    for (i2 = 1;i2 <= ad_count2; ++i2)
    {
      cr = i4stack_1_2[i4stack_1_2i];
      i4stack_1_2i = i4stack_1_2i - 1;
      ad_count1 = i4stack_1_2[i4stack_1_2i];
      i4stack_1_2i = i4stack_1_2i - 1;
      
      for (i1 = 1;i1 <= ad_count1; ++i1)
      {
        ca = i4stack_1_2[i4stack_1_2i];
        i4stack_1_2i = i4stack_1_2i - 1;
        ad_count0 = i4stack_1_2[i4stack_1_2i];
        i4stack_1_2i = i4stack_1_2i - 1;
        
        for (i0 = 1;i0 <= ad_count0; ++i0)
        {
          cp = i4stack_1_2[i4stack_1_2i];
          i4stack_1_2i = i4stack_1_2i - 1;
          ad_count = i4stack_1_2[i4stack_1_2i];
          i4stack_1_2i = i4stack_1_2i - 1;
          
          for (i = 1;i <= ad_count; ++i)
          {
            cs = i4stack_1_2[i4stack_1_2i];
            i4stack_1_2i = i4stack_1_2i - 1;
            cb2_par[cf][cr][cs][ca][cp][sim_idx] = cb2_par[cf][cr][cs][ca][cp][sim_idx] + Wt_age_mid[ca][cp][sim_idx] * dcatchbiomassb2_par;
          }
        }
      }
    }
    
    cf = i4stack_1_2[i4stack_1_2i];
    i4stack_1_2i = i4stack_1_2i - 1;
    dCatchBiomass = r4stack_1_2[r4stack_1_2i];
    r4stack_1_2i = r4stack_1_2i - 1;
  }
  
  POPDYN_PROJECTION_PAR_BPAR(par,parb2_par,npar,nfixed,TAE,FbyPar,FbyFixed,ECurrent,qy,R0,M,mat,Idist,Len_age,Wt_age,sel,mov,h,Recdist,Recdevs,RecSpatialDevs,SRrel,N,nb2_par,NBefore,nbeforeb2_par,SSN,C,cb2_par,SSBA,1,sim_idx);
}

// ----------------------------------------------------------------------------

//   Differentiation of operatingmodelbase__popdyn_projection_par in reverse (adjoint) mode:
//    gradient     of useful results: c
//    with respect to varying inputs: par
void D_OperatingModelBase::POPDYN_PROJECTION_PAR_BPAR(const ARRAY_1D par/* 0:npar - 1 */, ARRAY_1D parb2_par/* 0:npar - 1 */, int npar, int nfixed, const ARRAY_1D TAE/* 0:nfixed - 1 */, const ARRAY_1I FbyPar/* 0:npar - 1 */, const ARRAY_1I FbyFixed/* 0:nfixed - 1 */, const ARRAY_4D ECurrent/* nfleets,nareas,nsubyears,nsim */, const ARRAY_2D qy/* nfleets,nsim */, const ARRAY_2D R0/* npop,nsim */, const ARRAY_3D M/* nages,npop,nsim */, const ARRAY_3D mat/* nages,npop,nsim */, const ARRAY_4D Idist/* nareas,nages,npop,nsim */, const ARRAY_3D Len_age/* nages,npop,nsim */, const ARRAY_3D Wt_age/* nages,npop,nsim */, const ARRAY_3D sel/* nages,nfleets,nsim */, const ARRAY_6D mov/* nareas,nareas,nsubyears,nages,npop,nsim */, const ARRAY_2D h/* npop,nsim */, const ARRAY_3D Recdist/* nareas,npop,nsim */, const ARRAY_3D Recdevs/* SpawnPerYr,npop,nsim */, const ARRAY_3D RecSpatialDevs/* nareas,npop,nsim */, const ARRAY_1I SRrel/* npop */, ARRAY_5D N/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nb2_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D NBefore/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nbeforeb2_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D SSN/* nareas,nsubyears,nages,npop,nsim */, ARRAY_6D C/* nfleets,nareas,nsubyears,nages,npop,nsim */, ARRAY_6D cb2_par/* nfleets,nareas,nsubyears,nages,npop,nsim */, ARRAY_2D SSBA/* npop,nsim */, int bIgnoreLast, int sim_idx)
{
  int ad_count;
  int ad_count0;
  int ad_count1;
  int ad_count2;
  int ad_count3;
  int cf;
  int cr;
  int cs;
  int cx;
  int i;
  int i0;
  int i1;
  int i2;
  int i3;
  int ix_0___;
  cf = 0;
  cr = 1;
  ad_count3 = 0;
  
  while ((cr <= nareas))
  {
    cx = 0;
    ad_count0 = 0;
    
    while ((cx < npar))
    {
      i4stack_2_2i = i4stack_2_2i + 1;
      
      if (i4stack_2_2i > stackSizeInt(i4stack_2_2))
      {
        growStack(i4stack_2_2,i4stack_2_2i);
      }
      
      i4stack_2_2[i4stack_2_2i] = cf;
      cf = FbyPar[cx];
      cs = 1;
      ad_count = 0;
      
      while ((cs <= nsubyears))
      {
        EforYear[cf][cr][cs][sim_idx] = exp(par[cx]) * ECurrent[cf][cr][cs][sim_idx];
        i4stack_2_2i = i4stack_2_2i + 1;
        
        if (i4stack_2_2i > stackSizeInt(i4stack_2_2))
        {
          growStack(i4stack_2_2,i4stack_2_2i);
        }
        
        i4stack_2_2[i4stack_2_2i] = cs;
        cs = cs + 1;
        ad_count = ad_count + 1;
      }
      
      i4stack_2_2i = i4stack_2_2i + 1;
      
      if (i4stack_2_2i > stackSizeInt(i4stack_2_2))
      {
        growStack(i4stack_2_2,i4stack_2_2i);
      }
      
      i4stack_2_2[i4stack_2_2i] = ad_count;
      i4stack_2_2i = i4stack_2_2i + 1;
      
      if (i4stack_2_2i > stackSizeInt(i4stack_2_2))
      {
        growStack(i4stack_2_2,i4stack_2_2i);
      }
      
      i4stack_2_2[i4stack_2_2i] = cx;
      cx = cx + 1;
      ad_count0 = ad_count0 + 1;
    }
    
    i4stack_2_2i = i4stack_2_2i + 1;
    
    if (i4stack_2_2i > stackSizeInt(i4stack_2_2))
    {
      growStack(i4stack_2_2,i4stack_2_2i);
    }
    
    i4stack_2_2[i4stack_2_2i] = ad_count0;
    cx = 0;
    ad_count2 = 0;
    
    while ((cx < nfixed))
    {
      i4stack_2_2i = i4stack_2_2i + 1;
      
      if (i4stack_2_2i > stackSizeInt(i4stack_2_2))
      {
        growStack(i4stack_2_2,i4stack_2_2i);
      }
      
      i4stack_2_2[i4stack_2_2i] = cf;
      cf = FbyFixed[cx];
      cs = 1;
      ad_count1 = 0;
      
      while ((cs <= nsubyears))
      {
        EforYear[cf][cr][cs][sim_idx] = TAE[cx] * ECurrent[cf][cr][cs][sim_idx];
        i4stack_2_2i = i4stack_2_2i + 1;
        
        if (i4stack_2_2i > stackSizeInt(i4stack_2_2))
        {
          growStack(i4stack_2_2,i4stack_2_2i);
        }
        
        i4stack_2_2[i4stack_2_2i] = cs;
        cs = cs + 1;
        ad_count1 = ad_count1 + 1;
      }
      
      i4stack_2_2i = i4stack_2_2i + 1;
      
      if (i4stack_2_2i > stackSizeInt(i4stack_2_2))
      {
        growStack(i4stack_2_2,i4stack_2_2i);
      }
      
      i4stack_2_2[i4stack_2_2i] = ad_count1;
      cx = cx + 1;
      ad_count2 = ad_count2 + 1;
    }
    
    i4stack_2_2i = i4stack_2_2i + 1;
    
    if (i4stack_2_2i > stackSizeInt(i4stack_2_2))
    {
      growStack(i4stack_2_2,i4stack_2_2i);
    }
    
    i4stack_2_2[i4stack_2_2i] = ad_count2;
    i4stack_2_2i = i4stack_2_2i + 1;
    
    if (i4stack_2_2i > stackSizeInt(i4stack_2_2))
    {
      growStack(i4stack_2_2,i4stack_2_2i);
    }
    
    i4stack_2_2[i4stack_2_2i] = cr;
    cr = cr + 1;
    ad_count3 = ad_count3 + 1;
  }
  
  i4stack_2_2i = i4stack_2_2i + 1;
  
  if (i4stack_2_2i > stackSizeInt(i4stack_2_2))
  {
    growStack(i4stack_2_2,i4stack_2_2i);
  }
  
  i4stack_2_2[i4stack_2_2i] = ad_count3;
  popdyn_next_year(N,NBefore,sim_idx);
  POPDYN_YEAR_BPAR(qy,R0,M,mat,Len_age,Wt_age,sel,EforYear,eforyearb2_par,mov,h,Recdist,Recdevs,RecSpatialDevs,SRrel,N,nb2_par,NBefore,nbeforeb2_par,SSN,C,cb2_par,SSBA,bIgnoreLast,sim_idx);
  
  for (ix_0___ = 0;ix_0___ <= npar - 1; ++ix_0___)
  {
    parb2_par[ix_0___] = 0.0;
  }
  
  ad_count3 = i4stack_2_2[i4stack_2_2i];
  i4stack_2_2i = i4stack_2_2i - 1;
  
  for (i3 = 1;i3 <= ad_count3; ++i3)
  {
    cr = i4stack_2_2[i4stack_2_2i];
    i4stack_2_2i = i4stack_2_2i - 1;
    ad_count2 = i4stack_2_2[i4stack_2_2i];
    i4stack_2_2i = i4stack_2_2i - 1;
    
    for (i2 = 1;i2 <= ad_count2; ++i2)
    {
      ad_count1 = i4stack_2_2[i4stack_2_2i];
      i4stack_2_2i = i4stack_2_2i - 1;
      
      for (i1 = 1;i1 <= ad_count1; ++i1)
      {
        cs = i4stack_2_2[i4stack_2_2i];
        i4stack_2_2i = i4stack_2_2i - 1;
        eforyearb2_par[cf][cr][cs][sim_idx] = 0.0;
      }
      
      cf = i4stack_2_2[i4stack_2_2i];
      i4stack_2_2i = i4stack_2_2i - 1;
    }
    
    ad_count0 = i4stack_2_2[i4stack_2_2i];
    i4stack_2_2i = i4stack_2_2i - 1;
    
    for (i0 = 1;i0 <= ad_count0; ++i0)
    {
      cx = i4stack_2_2[i4stack_2_2i];
      i4stack_2_2i = i4stack_2_2i - 1;
      ad_count = i4stack_2_2[i4stack_2_2i];
      i4stack_2_2i = i4stack_2_2i - 1;
      
      for (i = 1;i <= ad_count; ++i)
      {
        cs = i4stack_2_2[i4stack_2_2i];
        i4stack_2_2i = i4stack_2_2i - 1;
        parb2_par[cx] = parb2_par[cx] + ECurrent[cf][cr][cs][sim_idx] * exp(par[cx]) * eforyearb2_par[cf][cr][cs][sim_idx];
        eforyearb2_par[cf][cr][cs][sim_idx] = 0.0;
      }
      
      cf = i4stack_2_2[i4stack_2_2i];
      i4stack_2_2i = i4stack_2_2i - 1;
    }
  }
}

// ----------------------------------------------------------------------------

//   Differentiation of operatingmodelbase__popdyn_year in reverse (adjoint) mode:
//    gradient     of useful results: c
//    with respect to varying inputs: eannual
void D_OperatingModelBase::POPDYN_YEAR_BPAR(const ARRAY_2D qy/* nfleets,nsim */, const ARRAY_2D R0/* npop,nsim */, const ARRAY_3D M/* nages,npop,nsim */, const ARRAY_3D mat/* nages,npop,nsim */, const ARRAY_3D Len_age/* nages,npop,nsim */, const ARRAY_3D Wt_age/* nages,npop,nsim */, const ARRAY_3D sel/* nages,nfleets,nsim */, const ARRAY_4D Eannual/* nfleets,nareas,nsubyears,nsim */, ARRAY_4D eannualb2_par/* nfleets,nareas,nsubyears,nsim */, const ARRAY_6D mov/* nareas,nareas,nsubyears,nages,npop,nsim */, const ARRAY_2D h/* npop,nsim */, const ARRAY_3D Recdist/* nareas,npop,nsim */, const ARRAY_3D Recdevs/* SpawnPerYr,npop,nsim */, const ARRAY_3D RecSpatialDevs/* nareas,npop,nsim */, const ARRAY_1I SRrel/* npop */, ARRAY_5D N/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nb2_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D NBefore/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D nbeforeb2_par/* nareas,nsubyears + 1,nages,npop,nsim */, ARRAY_5D SSN/* nareas,nsubyears,nages,npop,nsim */, ARRAY_6D C/* nfleets,nareas,nsubyears,nages,npop,nsim */, ARRAY_6D cb2_par/* nfleets,nareas,nsubyears,nages,npop,nsim */, ARRAY_2D SSBA/* npop,nsim */, int bIgnoreLast, int sim_idx)
{
  int ad_count;
  int ad_count0;
  int ad_count1;
  int ad_count10;
  int ad_count11;
  int ad_count12;
  int ad_count13;
  int ad_count2;
  int ad_count3;
  int ad_count4;
  int ad_count5;
  int ad_count6;
  int ad_count7;
  int ad_count8;
  int ad_count9;
  int branch;
  int ca;
  int cf;
  int cp;
  int cr;
  int cr2;
  int cs;
  double dFM;
  double dfmb2_par;
  double dFtot;
  double dftotb2_par;
  double dN;
  double dnb2_par;
  double dPlusGroup;
  double dplusgroupb2_par;
  double dRecruitment;
  double drecruitmentb2_par;
  double dSSB;
  double dSSB_area;
  double dssb_areab2_par;
  double dssbb2_par;
  double dSSN;
  double dssnb2_par;
  double dZ;
  double dzb2_par;
  int i;
  int i0;
  int i1;
  int i10;
  int i11;
  int i12;
  int i13;
  int i2;
  int i3;
  int i4;
  int i5;
  int i6;
  int i7;
  int i8;
  int i9;
  int ix_0___;
  int ix_1___;
  int ix_2___;
  int ix_3___;
  int ix_4___;
  int nRecdevIdx;
  double temp;
  double temp0;
  double temp1;
  double temp2;
  double tempb2_par;
  double tempb2_par0;
  double tempb2_par1;
  double tempb2_par2;
  dSSB = 0;
  dZ = 0;
  branch = 0;
  nRecdevIdx = 1;
  cs = 1;
  ad_count13 = 0;
  
  while ((cs <= nsubyears))
  {
    cp = 1;
    ad_count12 = 0;
    
    while ((cp <= npop))
    {
      r4stack_3_2i = r4stack_3_2i + 1;
      
      if (r4stack_3_2i > stackSizeInt(r4stack_3_2))
      {
        growStack(r4stack_3_2,r4stack_3_2i);
      }
      
      r4stack_3_2[r4stack_3_2i] = dSSB;
      dSSB = 0.0;
      cr = 1;
      ad_count0 = 0;
      
      while ((cr <= nareas))
      {
        dSSB_area = 0.0;
        ca = 1;
        ad_count = 0;
        
        while ((ca <= nages))
        {
          dSSN = NBefore[cr][cs][ca][cp][sim_idx] * mat[ca][cp][sim_idx];
          dSSB_area = dSSB_area + dSSN * Wt_age[ca][cp][sim_idx];
          i4stack_3_2i = i4stack_3_2i + 1;
          
          if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
          {
            growStack(i4stack_3_2,i4stack_3_2i);
          }
          
          i4stack_3_2[i4stack_3_2i] = ca;
          ca = ca + 1;
          ad_count = ad_count + 1;
        }
        
        i4stack_3_2i = i4stack_3_2i + 1;
        
        if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
        {
          growStack(i4stack_3_2,i4stack_3_2i);
        }
        
        i4stack_3_2[i4stack_3_2i] = ad_count;
        dSSB = dSSB + dSSB_area;
        i4stack_3_2i = i4stack_3_2i + 1;
        
        if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
        {
          growStack(i4stack_3_2,i4stack_3_2i);
        }
        
        i4stack_3_2[i4stack_3_2i] = cr;
        cr = cr + 1;
        ad_count0 = ad_count0 + 1;
      }
      
      i4stack_3_2i = i4stack_3_2i + 1;
      
      if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
      {
        growStack(i4stack_3_2,i4stack_3_2i);
      }
      
      i4stack_3_2[i4stack_3_2i] = ad_count0;
      
      if ((Recsubyr[cs] != 0))
      {
        if ((SRrel[cp] == 1))
        {
          dRecruitment = Recdevs[nRecdevIdx][cp][sim_idx] * (0.8 * R0[cp][sim_idx] * h[cp][sim_idx] * dSSB / (0.2 * SSBpR[cp][sim_idx] * R0[cp][sim_idx] * (1.0 - h[cp][sim_idx]) + (h[cp][sim_idx] - 0.2) * dSSB));
          bstack_3_2i = bstack_3_2i + 1;
          
          if (bstack_3_2i > stackSizeInt(bstack_3_2))
          {
            growStack(bstack_3_2,bstack_3_2i);
          }
          
          bstack_3_2[bstack_3_2i] = 0;
        }
        else
        {
          dRecruitment = Recdevs[nRecdevIdx][cp][sim_idx] * aR[cp][sim_idx] * dSSB * exp(-(bR[cp][sim_idx] * dSSB));
          bstack_3_2i = bstack_3_2i + 1;
          
          if (bstack_3_2i > stackSizeInt(bstack_3_2))
          {
            growStack(bstack_3_2,bstack_3_2i);
          }
          
          bstack_3_2[bstack_3_2i] = 1;
        }
        
        cr = 1;
        ad_count1 = 0;
        
        while ((cr <= nareas))
        {
          NBefore[cr][cs][1][cp][sim_idx] = dRecruitment * RecSpatialDevs[cr][cp][sim_idx] * Recdist[cr][cp][sim_idx];
          r4stack_3_2i = r4stack_3_2i + 1;
          
          if (r4stack_3_2i > stackSizeInt(r4stack_3_2))
          {
            growStack(r4stack_3_2,r4stack_3_2i);
          }
          
          r4stack_3_2[r4stack_3_2i] = N[cr][cs][1][cp][sim_idx];
          N[cr][cs][1][cp][sim_idx] = NBefore[cr][cs][1][cp][sim_idx];
          i4stack_3_2i = i4stack_3_2i + 1;
          
          if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
          {
            growStack(i4stack_3_2,i4stack_3_2i);
          }
          
          i4stack_3_2[i4stack_3_2i] = cr;
          cr = cr + 1;
          ad_count1 = ad_count1 + 1;
        }
        
        i4stack_3_2i = i4stack_3_2i + 1;
        
        if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
        {
          growStack(i4stack_3_2,i4stack_3_2i);
        }
        
        i4stack_3_2[i4stack_3_2i] = ad_count1;
        bstack_3_2i = bstack_3_2i + 1;
        
        if (bstack_3_2i > stackSizeInt(bstack_3_2))
        {
          growStack(bstack_3_2,bstack_3_2i);
        }
        
        bstack_3_2[bstack_3_2i] = 0;
      }
      else
      {
        bstack_3_2i = bstack_3_2i + 1;
        
        if (bstack_3_2i > stackSizeInt(bstack_3_2))
        {
          growStack(bstack_3_2,bstack_3_2i);
        }
        
        bstack_3_2[bstack_3_2i] = 1;
      }
      
      ca = 1;
      ad_count5 = 0;
      
      while ((ca <= nages))
      {
        cr = 1;
        ad_count3 = 0;
        
        while ((cr <= nareas))
        {
          dN = 0.0;
          cr2 = 1;
          ad_count2 = 0;
          
          while ((cr2 <= nareas))
          {
            dN = dN + N[cr2][cs][ca][cp][sim_idx] * mov[cr][cr2][cs][ca][cp][sim_idx];
            i4stack_3_2i = i4stack_3_2i + 1;
            
            if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
            {
              growStack(i4stack_3_2,i4stack_3_2i);
            }
            
            i4stack_3_2[i4stack_3_2i] = cr2;
            cr2 = cr2 + 1;
            ad_count2 = ad_count2 + 1;
          }
          
          i4stack_3_2i = i4stack_3_2i + 1;
          
          if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
          {
            growStack(i4stack_3_2,i4stack_3_2i);
          }
          
          i4stack_3_2[i4stack_3_2i] = ad_count2;
          MovN[cr][sim_idx] = dN;
          i4stack_3_2i = i4stack_3_2i + 1;
          
          if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
          {
            growStack(i4stack_3_2,i4stack_3_2i);
          }
          
          i4stack_3_2[i4stack_3_2i] = cr;
          cr = cr + 1;
          ad_count3 = ad_count3 + 1;
        }
        
        i4stack_3_2i = i4stack_3_2i + 1;
        
        if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
        {
          growStack(i4stack_3_2,i4stack_3_2i);
        }
        
        i4stack_3_2[i4stack_3_2i] = ad_count3;
        cr = 1;
        ad_count4 = 0;
        
        while ((cr <= nareas))
        {
          r4stack_3_2i = r4stack_3_2i + 1;
          
          if (r4stack_3_2i > stackSizeInt(r4stack_3_2))
          {
            growStack(r4stack_3_2,r4stack_3_2i);
          }
          
          r4stack_3_2[r4stack_3_2i] = N[cr][cs][ca][cp][sim_idx];
          N[cr][cs][ca][cp][sim_idx] = MovN[cr][sim_idx];
          i4stack_3_2i = i4stack_3_2i + 1;
          
          if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
          {
            growStack(i4stack_3_2,i4stack_3_2i);
          }
          
          i4stack_3_2[i4stack_3_2i] = cr;
          cr = cr + 1;
          ad_count4 = ad_count4 + 1;
        }
        
        i4stack_3_2i = i4stack_3_2i + 1;
        
        if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
        {
          growStack(i4stack_3_2,i4stack_3_2i);
        }
        
        i4stack_3_2[i4stack_3_2i] = ad_count4;
        i4stack_3_2i = i4stack_3_2i + 1;
        
        if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
        {
          growStack(i4stack_3_2,i4stack_3_2i);
        }
        
        i4stack_3_2[i4stack_3_2i] = ca;
        ca = ca + 1;
        ad_count5 = ad_count5 + 1;
      }
      
      i4stack_3_2i = i4stack_3_2i + 1;
      
      if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
      {
        growStack(i4stack_3_2,i4stack_3_2i);
      }
      
      i4stack_3_2[i4stack_3_2i] = ad_count5;
      ca = 1;
      ad_count9 = 0;
      
      while ((ca <= nages))
      {
        cr = 1;
        ad_count8 = 0;
        
        while ((cr <= nareas))
        {
          dFtot = 0.0;
          cf = 1;
          ad_count6 = 0;
          
          while ((cf <= nfleets))
          {
            dFM = Eannual[cf][cr][cs][sim_idx] * sel[ca][cf][sim_idx] * qy[cf][sim_idx];
            r4stack_3_2i = r4stack_3_2i + 1;
            
            if (r4stack_3_2i > stackSizeInt(r4stack_3_2))
            {
              growStack(r4stack_3_2,r4stack_3_2i);
            }
            
            r4stack_3_2[r4stack_3_2i] = FM[cf][sim_idx];
            FM[cf][sim_idx] = dFM;
            dFtot = dFtot + dFM;
            i4stack_3_2i = i4stack_3_2i + 1;
            
            if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
            {
              growStack(i4stack_3_2,i4stack_3_2i);
            }
            
            i4stack_3_2[i4stack_3_2i] = cf;
            cf = cf + 1;
            ad_count6 = ad_count6 + 1;
          }
          
          i4stack_3_2i = i4stack_3_2i + 1;
          
          if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
          {
            growStack(i4stack_3_2,i4stack_3_2i);
          }
          
          i4stack_3_2[i4stack_3_2i] = ad_count6;
          r4stack_3_2i = r4stack_3_2i + 1;
          
          if (r4stack_3_2i > stackSizeInt(r4stack_3_2))
          {
            growStack(r4stack_3_2,r4stack_3_2i);
          }
          
          r4stack_3_2[r4stack_3_2i] = dZ;
          dZ = dFtot + M[ca][cp][sim_idx] / nsubyears;
          cf = 1;
          ad_count7 = 0;
          
          while ((cf <= nfleets))
          {
            i4stack_3_2i = i4stack_3_2i + 1;
            
            if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
            {
              growStack(i4stack_3_2,i4stack_3_2i);
            }
            
            i4stack_3_2[i4stack_3_2i] = cf;
            cf = cf + 1;
            ad_count7 = ad_count7 + 1;
          }
          
          i4stack_3_2i = i4stack_3_2i + 1;
          
          if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
          {
            growStack(i4stack_3_2,i4stack_3_2i);
          }
          
          i4stack_3_2[i4stack_3_2i] = ad_count7;
          r4stack_3_2i = r4stack_3_2i + 1;
          
          if (r4stack_3_2i > stackSizeInt(r4stack_3_2))
          {
            growStack(r4stack_3_2,r4stack_3_2i);
          }
          
          r4stack_3_2[r4stack_3_2i] = N[cr][cs][ca][cp][sim_idx];
          N[cr][cs][ca][cp][sim_idx] = N[cr][cs][ca][cp][sim_idx] * exp(-dZ);
          i4stack_3_2i = i4stack_3_2i + 1;
          
          if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
          {
            growStack(i4stack_3_2,i4stack_3_2i);
          }
          
          i4stack_3_2[i4stack_3_2i] = cr;
          cr = cr + 1;
          ad_count8 = ad_count8 + 1;
        }
        
        i4stack_3_2i = i4stack_3_2i + 1;
        
        if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
        {
          growStack(i4stack_3_2,i4stack_3_2i);
        }
        
        i4stack_3_2[i4stack_3_2i] = ad_count8;
        i4stack_3_2i = i4stack_3_2i + 1;
        
        if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
        {
          growStack(i4stack_3_2,i4stack_3_2i);
        }
        
        i4stack_3_2[i4stack_3_2i] = ca;
        ca = ca + 1;
        ad_count9 = ad_count9 + 1;
      }
      
      i4stack_3_2i = i4stack_3_2i + 1;
      
      if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
      {
        growStack(i4stack_3_2,i4stack_3_2i);
      }
      
      i4stack_3_2[i4stack_3_2i] = ad_count9;
      
      if ((cs != nsubyears) || (bIgnoreLast == 0))
      {
        cr = 1;
        ad_count11 = 0;
        
        while ((cr <= nareas))
        {
          dPlusGroup = N[cr][cs][nages][cp][sim_idx];
          NBefore[cr][cs + 1][1][cp][sim_idx] = 0.0;
          r4stack_3_2i = r4stack_3_2i + 1;
          
          if (r4stack_3_2i > stackSizeInt(r4stack_3_2))
          {
            growStack(r4stack_3_2,r4stack_3_2i);
          }
          
          r4stack_3_2[r4stack_3_2i] = N[cr][cs + 1][1][cp][sim_idx];
          N[cr][cs + 1][1][cp][sim_idx] = 0.0;
          ca = nages - 1;
          ad_count10 = 0;
          
          while ((ca >= 1))
          {
            NBefore[cr][cs + 1][ca + 1][cp][sim_idx] = N[cr][cs][ca][cp][sim_idx];
            r4stack_3_2i = r4stack_3_2i + 1;
            
            if (r4stack_3_2i > stackSizeInt(r4stack_3_2))
            {
              growStack(r4stack_3_2,r4stack_3_2i);
            }
            
            r4stack_3_2[r4stack_3_2i] = N[cr][cs + 1][ca + 1][cp][sim_idx];
            N[cr][cs + 1][ca + 1][cp][sim_idx] = NBefore[cr][cs + 1][ca + 1][cp][sim_idx];
            i4stack_3_2i = i4stack_3_2i + 1;
            
            if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
            {
              growStack(i4stack_3_2,i4stack_3_2i);
            }
            
            i4stack_3_2[i4stack_3_2i] = ca;
            ca = ca - 1;
            ad_count10 = ad_count10 + 1;
          }
          
          i4stack_3_2i = i4stack_3_2i + 1;
          
          if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
          {
            growStack(i4stack_3_2,i4stack_3_2i);
          }
          
          i4stack_3_2[i4stack_3_2i] = ad_count10;
          NBefore[cr][cs + 1][nages][cp][sim_idx] = NBefore[cr][cs + 1][nages][cp][sim_idx] + dPlusGroup;
          r4stack_3_2i = r4stack_3_2i + 1;
          
          if (r4stack_3_2i > stackSizeInt(r4stack_3_2))
          {
            growStack(r4stack_3_2,r4stack_3_2i);
          }
          
          r4stack_3_2[r4stack_3_2i] = N[cr][cs + 1][nages][cp][sim_idx];
          N[cr][cs + 1][nages][cp][sim_idx] = N[cr][cs + 1][nages][cp][sim_idx] + dPlusGroup;
          i4stack_3_2i = i4stack_3_2i + 1;
          
          if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
          {
            growStack(i4stack_3_2,i4stack_3_2i);
          }
          
          i4stack_3_2[i4stack_3_2i] = cr;
          cr = cr + 1;
          ad_count11 = ad_count11 + 1;
        }
        
        i4stack_3_2i = i4stack_3_2i + 1;
        
        if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
        {
          growStack(i4stack_3_2,i4stack_3_2i);
        }
        
        i4stack_3_2[i4stack_3_2i] = ad_count11;
        bstack_3_2i = bstack_3_2i + 1;
        
        if (bstack_3_2i > stackSizeInt(bstack_3_2))
        {
          growStack(bstack_3_2,bstack_3_2i);
        }
        
        bstack_3_2[bstack_3_2i] = 0;
      }
      else
      {
        bstack_3_2i = bstack_3_2i + 1;
        
        if (bstack_3_2i > stackSizeInt(bstack_3_2))
        {
          growStack(bstack_3_2,bstack_3_2i);
        }
        
        bstack_3_2[bstack_3_2i] = 1;
      }
      
      i4stack_3_2i = i4stack_3_2i + 1;
      
      if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
      {
        growStack(i4stack_3_2,i4stack_3_2i);
      }
      
      i4stack_3_2[i4stack_3_2i] = cp;
      cp = cp + 1;
      ad_count12 = ad_count12 + 1;
    }
    
    i4stack_3_2i = i4stack_3_2i + 1;
    
    if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
    {
      growStack(i4stack_3_2,i4stack_3_2i);
    }
    
    i4stack_3_2[i4stack_3_2i] = ad_count12;
    
    if ((Recsubyr[cs] != 0))
    {
      i4stack_3_2i = i4stack_3_2i + 1;
      
      if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
      {
        growStack(i4stack_3_2,i4stack_3_2i);
      }
      
      i4stack_3_2[i4stack_3_2i] = nRecdevIdx;
      nRecdevIdx = nRecdevIdx + 1;
      bstack_3_2i = bstack_3_2i + 1;
      
      if (bstack_3_2i > stackSizeInt(bstack_3_2))
      {
        growStack(bstack_3_2,bstack_3_2i);
      }
      
      bstack_3_2[bstack_3_2i] = 0;
    }
    else
    {
      bstack_3_2i = bstack_3_2i + 1;
      
      if (bstack_3_2i > stackSizeInt(bstack_3_2))
      {
        growStack(bstack_3_2,bstack_3_2i);
      }
      
      bstack_3_2[bstack_3_2i] = 1;
    }
    
    i4stack_3_2i = i4stack_3_2i + 1;
    
    if (i4stack_3_2i > stackSizeInt(i4stack_3_2))
    {
      growStack(i4stack_3_2,i4stack_3_2i);
    }
    
    i4stack_3_2[i4stack_3_2i] = cs;
    cs = cs + 1;
    ad_count13 = ad_count13 + 1;
  }
  
  for (ix_1___ = 1;ix_1___ <= nsim; ++ix_1___)
  {
    for (ix_0___ = 1;ix_0___ <= nareas; ++ix_0___)
    {
      movnb2_par[ix_0___][ix_1___] = 0.0;
    }
  }
  
  for (ix_1___ = 1;ix_1___ <= nsim; ++ix_1___)
  {
    for (ix_0___ = 1;ix_0___ <= nfleets; ++ix_0___)
    {
      fmb2_par[ix_0___][ix_1___] = 0.0;
    }
  }
  
  for (ix_4___ = 1;ix_4___ <= nsim; ++ix_4___)
  {
    for (ix_3___ = 1;ix_3___ <= npop; ++ix_3___)
    {
      for (ix_2___ = 1;ix_2___ <= nages; ++ix_2___)
      {
        for (ix_1___ = 1;ix_1___ <= nsubyears + 1; ++ix_1___)
        {
          for (ix_0___ = 1;ix_0___ <= nareas; ++ix_0___)
          {
            nbeforeb2_par[ix_0___][ix_1___][ix_2___][ix_3___][ix_4___] = 0.0;
          }
        }
      }
    }
  }
  
  for (ix_4___ = 1;ix_4___ <= nsim; ++ix_4___)
  {
    for (ix_3___ = 1;ix_3___ <= npop; ++ix_3___)
    {
      for (ix_2___ = 1;ix_2___ <= nages; ++ix_2___)
      {
        for (ix_1___ = 1;ix_1___ <= nsubyears + 1; ++ix_1___)
        {
          for (ix_0___ = 1;ix_0___ <= nareas; ++ix_0___)
          {
            nb2_par[ix_0___][ix_1___][ix_2___][ix_3___][ix_4___] = 0.0;
          }
        }
      }
    }
  }
  
  for (ix_3___ = 1;ix_3___ <= nsim; ++ix_3___)
  {
    for (ix_2___ = 1;ix_2___ <= nsubyears; ++ix_2___)
    {
      for (ix_1___ = 1;ix_1___ <= nareas; ++ix_1___)
      {
        for (ix_0___ = 1;ix_0___ <= nfleets; ++ix_0___)
        {
          eannualb2_par[ix_0___][ix_1___][ix_2___][ix_3___] = 0.0;
        }
      }
    }
  }
  
  for (i13 = 1;i13 <= ad_count13; ++i13)
  {
    cs = i4stack_3_2[i4stack_3_2i];
    i4stack_3_2i = i4stack_3_2i - 1;
    branch = bstack_3_2[bstack_3_2i];
    bstack_3_2i = bstack_3_2i - 1;
    nRecdevIdx = i4stack_3_2[i4stack_3_2i];
    i4stack_3_2i = i4stack_3_2i - 1;
    ad_count12 = i4stack_3_2[i4stack_3_2i];
    i4stack_3_2i = i4stack_3_2i - 1;
    
    for (i12 = 1;i12 <= ad_count12; ++i12)
    {
      cp = i4stack_3_2[i4stack_3_2i];
      i4stack_3_2i = i4stack_3_2i - 1;
      branch = bstack_3_2[bstack_3_2i];
      bstack_3_2i = bstack_3_2i - 1;
      
      if ((branch == 0))
      {
        ad_count11 = i4stack_3_2[i4stack_3_2i];
        i4stack_3_2i = i4stack_3_2i - 1;
        
        for (i11 = 1;i11 <= ad_count11; ++i11)
        {
          cr = i4stack_3_2[i4stack_3_2i];
          i4stack_3_2i = i4stack_3_2i - 1;
          N[cr][cs + 1][nages][cp][sim_idx] = r4stack_3_2[r4stack_3_2i];
          r4stack_3_2i = r4stack_3_2i - 1;
          dplusgroupb2_par = nbeforeb2_par[cr][cs + 1][nages][cp][sim_idx] + nb2_par[cr][cs + 1][nages][cp][sim_idx];
          ad_count10 = i4stack_3_2[i4stack_3_2i];
          i4stack_3_2i = i4stack_3_2i - 1;
          
          for (i10 = 1;i10 <= ad_count10; ++i10)
          {
            ca = i4stack_3_2[i4stack_3_2i];
            i4stack_3_2i = i4stack_3_2i - 1;
            N[cr][cs + 1][ca + 1][cp][sim_idx] = r4stack_3_2[r4stack_3_2i];
            r4stack_3_2i = r4stack_3_2i - 1;
            nbeforeb2_par[cr][cs + 1][ca + 1][cp][sim_idx] = nbeforeb2_par[cr][cs + 1][ca + 1][cp][sim_idx] + nb2_par[cr][cs + 1][ca + 1][cp][sim_idx];
            nb2_par[cr][cs + 1][ca + 1][cp][sim_idx] = 0.0;
            nb2_par[cr][cs][ca][cp][sim_idx] = nb2_par[cr][cs][ca][cp][sim_idx] + nbeforeb2_par[cr][cs + 1][ca + 1][cp][sim_idx];
            nbeforeb2_par[cr][cs + 1][ca + 1][cp][sim_idx] = 0.0;
          }
          
          N[cr][cs + 1][1][cp][sim_idx] = r4stack_3_2[r4stack_3_2i];
          r4stack_3_2i = r4stack_3_2i - 1;
          nb2_par[cr][cs + 1][1][cp][sim_idx] = 0.0;
          nbeforeb2_par[cr][cs + 1][1][cp][sim_idx] = 0.0;
          nb2_par[cr][cs][nages][cp][sim_idx] = nb2_par[cr][cs][nages][cp][sim_idx] + dplusgroupb2_par;
        }
      }
      
      ad_count9 = i4stack_3_2[i4stack_3_2i];
      i4stack_3_2i = i4stack_3_2i - 1;
      
      for (i9 = 1;i9 <= ad_count9; ++i9)
      {
        ca = i4stack_3_2[i4stack_3_2i];
        i4stack_3_2i = i4stack_3_2i - 1;
        ad_count8 = i4stack_3_2[i4stack_3_2i];
        i4stack_3_2i = i4stack_3_2i - 1;
        
        for (i8 = 1;i8 <= ad_count8; ++i8)
        {
          cr = i4stack_3_2[i4stack_3_2i];
          i4stack_3_2i = i4stack_3_2i - 1;
          N[cr][cs][ca][cp][sim_idx] = r4stack_3_2[r4stack_3_2i];
          r4stack_3_2i = r4stack_3_2i - 1;
          dzb2_par = -(exp(-dZ) * N[cr][cs][ca][cp][sim_idx] * nb2_par[cr][cs][ca][cp][sim_idx]);
          nb2_par[cr][cs][ca][cp][sim_idx] = exp(-dZ) * nb2_par[cr][cs][ca][cp][sim_idx];
          ad_count7 = i4stack_3_2[i4stack_3_2i];
          i4stack_3_2i = i4stack_3_2i - 1;
          
          for (i7 = 1;i7 <= ad_count7; ++i7)
          {
            cf = i4stack_3_2[i4stack_3_2i];
            i4stack_3_2i = i4stack_3_2i - 1;
            tempb2_par1 = (1 - exp(-dZ)) * cb2_par[cf][cr][cs][ca][cp][sim_idx];
            temp1 = FM[cf][sim_idx] / dZ;
            temp2 = N[cr][cs][ca][cp][sim_idx];
            tempb2_par2 = temp2 * tempb2_par1 / dZ;
            nb2_par[cr][cs][ca][cp][sim_idx] = nb2_par[cr][cs][ca][cp][sim_idx] + temp1 * tempb2_par1;
            fmb2_par[cf][sim_idx] = fmb2_par[cf][sim_idx] + tempb2_par2;
            dzb2_par = dzb2_par + exp(-dZ) * temp2 * temp1 * cb2_par[cf][cr][cs][ca][cp][sim_idx] - temp1 * tempb2_par2;
            cb2_par[cf][cr][cs][ca][cp][sim_idx] = 0.0;
          }
          
          dZ = r4stack_3_2[r4stack_3_2i];
          r4stack_3_2i = r4stack_3_2i - 1;
          dftotb2_par = dzb2_par;
          ad_count6 = i4stack_3_2[i4stack_3_2i];
          i4stack_3_2i = i4stack_3_2i - 1;
          
          for (i6 = 1;i6 <= ad_count6; ++i6)
          {
            cf = i4stack_3_2[i4stack_3_2i];
            i4stack_3_2i = i4stack_3_2i - 1;
            dfmb2_par = fmb2_par[cf][sim_idx] + dftotb2_par;
            FM[cf][sim_idx] = r4stack_3_2[r4stack_3_2i];
            r4stack_3_2i = r4stack_3_2i - 1;
            fmb2_par[cf][sim_idx] = 0.0;
            eannualb2_par[cf][cr][cs][sim_idx] = eannualb2_par[cf][cr][cs][sim_idx] + sel[ca][cf][sim_idx] * qy[cf][sim_idx] * dfmb2_par;
          }
        }
      }
      
      ad_count5 = i4stack_3_2[i4stack_3_2i];
      i4stack_3_2i = i4stack_3_2i - 1;
      
      for (i5 = 1;i5 <= ad_count5; ++i5)
      {
        ca = i4stack_3_2[i4stack_3_2i];
        i4stack_3_2i = i4stack_3_2i - 1;
        ad_count4 = i4stack_3_2[i4stack_3_2i];
        i4stack_3_2i = i4stack_3_2i - 1;
        
        for (i4 = 1;i4 <= ad_count4; ++i4)
        {
          cr = i4stack_3_2[i4stack_3_2i];
          i4stack_3_2i = i4stack_3_2i - 1;
          N[cr][cs][ca][cp][sim_idx] = r4stack_3_2[r4stack_3_2i];
          r4stack_3_2i = r4stack_3_2i - 1;
          movnb2_par[cr][sim_idx] = movnb2_par[cr][sim_idx] + nb2_par[cr][cs][ca][cp][sim_idx];
          nb2_par[cr][cs][ca][cp][sim_idx] = 0.0;
        }
        
        ad_count3 = i4stack_3_2[i4stack_3_2i];
        i4stack_3_2i = i4stack_3_2i - 1;
        
        for (i3 = 1;i3 <= ad_count3; ++i3)
        {
          cr = i4stack_3_2[i4stack_3_2i];
          i4stack_3_2i = i4stack_3_2i - 1;
          dnb2_par = movnb2_par[cr][sim_idx];
          movnb2_par[cr][sim_idx] = 0.0;
          ad_count2 = i4stack_3_2[i4stack_3_2i];
          i4stack_3_2i = i4stack_3_2i - 1;
          
          for (i2 = 1;i2 <= ad_count2; ++i2)
          {
            cr2 = i4stack_3_2[i4stack_3_2i];
            i4stack_3_2i = i4stack_3_2i - 1;
            nb2_par[cr2][cs][ca][cp][sim_idx] = nb2_par[cr2][cs][ca][cp][sim_idx] + mov[cr][cr2][cs][ca][cp][sim_idx] * dnb2_par;
          }
        }
      }
      
      branch = bstack_3_2[bstack_3_2i];
      bstack_3_2i = bstack_3_2i - 1;
      
      if ((branch == 0))
      {
        drecruitmentb2_par = 0.0;
        ad_count1 = i4stack_3_2[i4stack_3_2i];
        i4stack_3_2i = i4stack_3_2i - 1;
        
        for (i1 = 1;i1 <= ad_count1; ++i1)
        {
          cr = i4stack_3_2[i4stack_3_2i];
          i4stack_3_2i = i4stack_3_2i - 1;
          N[cr][cs][1][cp][sim_idx] = r4stack_3_2[r4stack_3_2i];
          r4stack_3_2i = r4stack_3_2i - 1;
          nbeforeb2_par[cr][cs][1][cp][sim_idx] = nbeforeb2_par[cr][cs][1][cp][sim_idx] + nb2_par[cr][cs][1][cp][sim_idx];
          nb2_par[cr][cs][1][cp][sim_idx] = 0.0;
          drecruitmentb2_par = drecruitmentb2_par + Recdist[cr][cp][sim_idx] * RecSpatialDevs[cr][cp][sim_idx] * nbeforeb2_par[cr][cs][1][cp][sim_idx];
          nbeforeb2_par[cr][cs][1][cp][sim_idx] = 0.0;
        }
        
        branch = bstack_3_2[bstack_3_2i];
        bstack_3_2i = bstack_3_2i - 1;
        
        if ((branch == 0))
        {
          temp = 0.2 * SSBpR[cp][sim_idx] * R0[cp][sim_idx] * (-h[cp][sim_idx] + 1.0) + (h[cp][sim_idx] - 0.2) * dSSB;
          tempb2_par = Recdevs[nRecdevIdx][cp][sim_idx] * h[cp][sim_idx] * R0[cp][sim_idx] * 0.8 * drecruitmentb2_par / temp;
          dssbb2_par = (1.0 - dSSB * (h[cp][sim_idx] - 0.2) / temp) * tempb2_par;
        }
        else
        {
          temp0 = -(bR[cp][sim_idx] * dSSB);
          tempb2_par0 = Recdevs[nRecdevIdx][cp][sim_idx] * aR[cp][sim_idx] * drecruitmentb2_par;
          dssbb2_par = (exp(temp0) - exp(temp0) * dSSB * bR[cp][sim_idx]) * tempb2_par0;
        }
      }
      else
      {
        dssbb2_par = 0.0;
      }
      
      ad_count0 = i4stack_3_2[i4stack_3_2i];
      i4stack_3_2i = i4stack_3_2i - 1;
      
      for (i0 = 1;i0 <= ad_count0; ++i0)
      {
        cr = i4stack_3_2[i4stack_3_2i];
        i4stack_3_2i = i4stack_3_2i - 1;
        dssb_areab2_par = dssbb2_par;
        ad_count = i4stack_3_2[i4stack_3_2i];
        i4stack_3_2i = i4stack_3_2i - 1;
        
        for (i = 1;i <= ad_count; ++i)
        {
          ca = i4stack_3_2[i4stack_3_2i];
          i4stack_3_2i = i4stack_3_2i - 1;
          dssnb2_par = Wt_age[ca][cp][sim_idx] * dssb_areab2_par;
          nbeforeb2_par[cr][cs][ca][cp][sim_idx] = nbeforeb2_par[cr][cs][ca][cp][sim_idx] + mat[ca][cp][sim_idx] * dssnb2_par;
        }
      }
      
      dSSB = r4stack_3_2[r4stack_3_2i];
      r4stack_3_2i = r4stack_3_2i - 1;
    }
  }
}

#include "OmB_impl_lib_interface_methods.hpp"
#include "OmB_impl_lib_interface_globals.hpp"
#include "OmB_impl_lib_interface_constructor.hpp"


