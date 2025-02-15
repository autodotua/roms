      SUBROUTINE read_BioPar (model, inp, out, Lwrite)
!
!=======================================================================
!                                                                      !
!  This routine reads in biological model input parameters.            !
!                                                                      !
!=======================================================================
!
      USE mod_param
      USE mod_parallel
      USE mod_biology
      USE mod_ncparam
      USE mod_scalars
!
      USE inp_decode_mod
!
      implicit none
!
!  Imported variable declarations
!
      logical, intent(in) :: Lwrite
      integer, intent(in) :: model, inp, out
!
!  Local variable declarations.
!
      integer :: Npts, Nval
      integer :: iTrcStr, iTrcEnd
      integer :: i, ifield, igrid, itracer, itrc, ng, nline, status

      logical, dimension(Ngrids) :: Lbio
      logical, dimension(NBT,Ngrids) :: Ltrc

      real(r8), dimension(NBT,Ngrids) :: Rbio

      real(dp), dimension(nRval) :: Rval

      character (len=40 ) :: KeyWord
      character (len=256) :: line
      character (len=256), dimension(nCval) :: Cval
!
!-----------------------------------------------------------------------
!  Initialize.
!-----------------------------------------------------------------------
!
      igrid=1                            ! nested grid counter
      itracer=0                          ! LBC tracer counter
      iTrcStr=1                          ! first LBC tracer to process
      iTrcEnd=NBT                        ! last  LBC tracer to process
      nline=0                            ! LBC multi-line counter
!-----------------------------------------------------------------------
!  Read in UMaine CoSiNE biological model parameters.
!-----------------------------------------------------------------------
!
      DO WHILE (.TRUE.)
        READ (inp,'(a)',ERR=10,END=20) line
        status=decode_line(line, KeyWord, Nval, Cval, Rval)
        IF (status.gt.0) THEN
          SELECT CASE (TRIM(KeyWord))
            CASE ('Lbiology')
              Npts=load_l(Nval, Cval, Ngrids, Lbiology)
            CASE ('BioIter')
              Npts=load_i(Nval, Rval, Ngrids, BioIter)
            CASE ('reg1')
              Npts=load_r(Nval, Rval, Ngrids, reg1)
            CASE ('reg2')
              Npts=load_r(Nval, Rval, Ngrids, reg2)
            CASE ('gmaxs1')
              Npts=load_r(Nval, Rval, Ngrids, gmaxs1)
            CASE ('gmaxs2')
              Npts=load_r(Nval, Rval, Ngrids, gmaxs2)
            CASE ('gmaxs3')
              Npts=load_r(Nval, Rval, Ngrids, gmaxs3)
            CASE ('beta1')
              Npts=load_r(Nval, Rval, Ngrids, beta1)
            CASE ('beta2')
              Npts=load_r(Nval, Rval, Ngrids, beta2)
            CASE ('akz1')
              Npts=load_r(Nval, Rval, Ngrids, akz1)
            CASE ('akz2')
              Npts=load_r(Nval, Rval, Ngrids, akz2)
            CASE ('PARfrac')
              Npts=load_r(Nval, Rval, Ngrids, PARfrac)
            CASE ('alphachl_s1')
              Npts=load_r(Nval, Rval, Ngrids, alphachl_s1)
            CASE ('alphachl_s2')
              Npts=load_r(Nval, Rval, Ngrids, alphachl_s2)
            CASE ('alphachl_s3')
              Npts=load_r(Nval, Rval, Ngrids, alphachl_s3)
            CASE ('pis1')
              Npts=load_r(Nval, Rval, Ngrids, pis1)
            CASE ('pis2')
              Npts=load_r(Nval, Rval, Ngrids, pis2)
            CASE ('pis3')
              Npts=load_r(Nval, Rval, Ngrids, pis3)
            CASE ('akno3s1')
              Npts=load_r(Nval, Rval, Ngrids, akno3s1)
            CASE ('akno3s2')
              Npts=load_r(Nval, Rval, Ngrids, akno3s2)
            CASE ('akno3s3')
              Npts=load_r(Nval, Rval, Ngrids, akno3s3)
            CASE ('aknh4s1')
              Npts=load_r(Nval, Rval, Ngrids, aknh4s1)
            CASE ('aknh4s2')
              Npts=load_r(Nval, Rval, Ngrids, aknh4s2)
            CASE ('aknh4s3')
              Npts=load_r(Nval, Rval, Ngrids, aknh4s3)
            CASE ('akpo4s1')
              Npts=load_r(Nval, Rval, Ngrids, akpo4s1)
            CASE ('akpo4s2')
              Npts=load_r(Nval, Rval, Ngrids, akpo4s2)
            CASE ('akpo4s3')
              Npts=load_r(Nval, Rval, Ngrids, akpo4s3)
            CASE ('akco2s1')
              Npts=load_r(Nval, Rval, Ngrids, akco2s1)
            CASE ('akco2s2')
              Npts=load_r(Nval, Rval, Ngrids, akco2s2)
            CASE ('akco2s3')
              Npts=load_r(Nval, Rval, Ngrids, akco2s3)
            CASE ('aksio4s2')
              Npts=load_r(Nval, Rval, Ngrids, aksio4s2)
            CASE ('ES1')
              Npts=load_r(Nval, Rval, Ngrids, ES1)
            CASE ('ES2')
              Npts=load_r(Nval, Rval, Ngrids, ES2)
            CASE ('ES3')
              Npts=load_r(Nval, Rval, Ngrids, ES3)
            CASE ('ak1')
              Npts=load_r(Nval, Rval, Ngrids, ak1)
            CASE ('ak2')
              Npts=load_r(Nval, Rval, Ngrids, ak2)
            CASE ('Qmax')
              Npts=load_r(Nval, Rval, Ngrids, Qmax)
            CASE ('Qmin')
              Npts=load_r(Nval, Rval, Ngrids, Qmin)
            CASE ('lambdano3_s1')
              Npts=load_r(Nval, Rval, Ngrids, lambdano3_s1)
            CASE ('lambdano3_s2')
              Npts=load_r(Nval, Rval, Ngrids, lambdano3_s2)
            CASE ('lambdano3_s3')
              Npts=load_r(Nval, Rval, Ngrids, lambdano3_s3)
            CASE ('thetaNmax_s1')
              Npts=load_r(Nval, Rval, Ngrids, thetaNmax_s1)
            CASE ('thetaNmax_s2')
              Npts=load_r(Nval, Rval, Ngrids, thetaNmax_s2)
            CASE ('thetaNmax_s3')
              Npts=load_r(Nval, Rval, Ngrids, thetaNmax_s3)
            CASE ('bgamma')
              Npts=load_r(Nval, Rval, Ngrids, bgamma)
            CASE ('bgamma1')
              Npts=load_r(Nval, Rval, Ngrids, bgamma1)
            CASE ('bgamma2')
              Npts=load_r(Nval, Rval, Ngrids, bgamma2)
            CASE ('bgamma22')
              Npts=load_r(Nval, Rval, Ngrids, bgamma22)
            CASE ('bgamma3')
              Npts=load_r(Nval, Rval, Ngrids, bgamma3)
            CASE ('bgamma4')
              Npts=load_r(Nval, Rval, Ngrids, bgamma4)
            CASE ('bgamma10')
              Npts=load_r(Nval, Rval, Ngrids, bgamma10)
            CASE ('bgamma12')
              Npts=load_r(Nval, Rval, Ngrids, bgamma12)
            CASE ('bgamma5')
              Npts=load_r(Nval, Rval, Ngrids, bgamma5)
            CASE ('bgamma7')
              Npts=load_r(Nval, Rval, Ngrids, bgamma7)
            CASE ('bgamma11')
              Npts=load_r(Nval, Rval, Ngrids, bgamma11)
            CASE ('bgamma13')
              Npts=load_r(Nval, Rval, Ngrids, bgamma13)
            CASE ('mtos1')
              Npts=load_r(Nval, Rval, Ngrids, mtos1)
            CASE ('mtos2')
              Npts=load_r(Nval, Rval, Ngrids, mtos2)
            CASE ('mtos3')
              Npts=load_r(Nval, Rval, Ngrids, mtos3)
            CASE ('flz1')
              Npts=load_r(Nval, Rval, Ngrids, flz1)
            CASE ('flz2')
              Npts=load_r(Nval, Rval, Ngrids, flz2)
            CASE ('lk1')
              Npts=load_r(Nval, Rval, Ngrids, lk1)
            CASE ('lk2')
              Npts=load_r(Nval, Rval, Ngrids, lk2)
            CASE ('lk3')
              Npts=load_r(Nval, Rval, Ngrids, lk3)
            CASE ('ratiol1')
              Npts=load_r(Nval, Rval, Ngrids, ratiol1)
            CASE ('ratiol2')
              Npts=load_r(Nval, Rval, Ngrids, ratiol2)
            CASE ('wsdn')
              Npts=load_r(Nval, Rval, Ngrids, wsdn)
            CASE ('wsdc')
              Npts=load_r(Nval, Rval, Ngrids, wsdc)
            CASE ('wsdsi')
              Npts=load_r(Nval, Rval, Ngrids, wsdsi)
            CASE ('wsdca')
              Npts=load_r(Nval, Rval, Ngrids, wsdca)
            CASE ('wsp1')
              Npts=load_r(Nval, Rval, Ngrids, wsp1)
            CASE ('wsp2')
              Npts=load_r(Nval, Rval, Ngrids, wsp2)
            CASE ('wsp3')
              Npts=load_r(Nval, Rval, Ngrids, wsp3)
            CASE ('pco2a')
              Npts=load_r(Nval, Rval, Ngrids, pco2a)
            CASE ('p2n')
              Npts=load_r(Nval, Rval, Ngrids, p2n)
            CASE ('o2no')
              Npts=load_r(Nval, Rval, Ngrids, o2no)
            CASE ('o2nh')
              Npts=load_r(Nval, Rval, Ngrids, o2nh)
            CASE ('cnb')
              Npts=load_r(Nval, Rval, Ngrids, cnb)
            CASE ('apsilon')
              Npts=load_r(Nval, Rval, Ngrids, apsilon)
            CASE ('ro5')
              Npts=load_r(Nval, Rval, Ngrids, ro5)
            CASE ('ro6')
              Npts=load_r(Nval, Rval, Ngrids, ro6)
            CASE ('ro7')
              Npts=load_r(Nval, Rval, Ngrids, ro7)
            CASE ('ro10')
              Npts=load_r(Nval, Rval, Ngrids, ro10)
            CASE ('rop')
              Npts=load_r(Nval, Rval, Ngrids, rop)
            CASE ('rob')
              Npts=load_r(Nval, Rval, Ngrids, rob)
            CASE ('kabac')
              Npts=load_r(Nval, Rval, Ngrids, kabac)
            CASE ('klbac')
              Npts=load_r(Nval, Rval, Ngrids, klbac)
            CASE ('ksdoc')
              Npts=load_r(Nval, Rval, Ngrids, ksdoc)
            CASE ('ksdon')
              Npts=load_r(Nval, Rval, Ngrids, ksdon)
            CASE ('ratiob')
              Npts=load_r(Nval, Rval, Ngrids, ratiob)
            CASE ('ratiobc')
              Npts=load_r(Nval, Rval, Ngrids, ratiobc)
            CASE ('RtUVLDOC')
              Npts=load_r(Nval, Rval, Ngrids, RtUVLDOC)
            CASE ('RtUVSDOC')
              Npts=load_r(Nval, Rval, Ngrids, RtUVSDOC)
            CASE ('RtUVLDIC')
              Npts=load_r(Nval, Rval, Ngrids, RtUVLDIC)
            CASE ('RtUVSDIC')
              Npts=load_r(Nval, Rval, Ngrids, RtUVSDIC)
            CASE ('colorFR1')
              Npts=load_r(Nval, Rval, Ngrids, colorFR1)
            CASE ('colorFR2')
              Npts=load_r(Nval, Rval, Ngrids, colorFR2)
# ifdef IRON_LIMIT
            CASE ('T_Fe')
              Npts=load_r(Nval, Rval, Ngrids, T_Fe)
            CASE ('A_Fe')
              Npts=load_r(Nval, Rval, Ngrids, A_Fe)
            CASE ('B_Fe')
              Npts=load_r(Nval, Rval, Ngrids, B_Fe)
            CASE ('S1_FeC')
              Npts=load_r(Nval, Rval, Ngrids, S1_FeC)
            CASE ('S2_FeC')
              Npts=load_r(Nval, Rval, Ngrids, S2_FeC)
            CASE ('S3_FeC')
              Npts=load_r(Nval, Rval, Ngrids, S3_FeC)
            CASE ('FeRR')
              Npts=load_r(Nval, Rval, Ngrids, FeRR)
# endif

            CASE ('TNU2')
              Npts=load_r(Nval, Rval, NBT, Ngrids, Rbio)
              DO ng=1,Ngrids
                DO itrc=1,NBT
                  i=idbio(itrc)
                  nl_tnu2(i,ng)=Rbio(itrc,ng)
                END DO
              END DO
            CASE ('TNU4')
              Npts=load_r(Nval, Rval, NBT, Ngrids, Rbio)
              DO ng=1,Ngrids
                DO itrc=1,NBT
                  i=idbio(itrc)
                  nl_tnu4(i,ng)=Rbio(itrc,ng)
                END DO
              END DO
            CASE ('ad_TNU2')
              Npts=load_r(Nval, Rval, NBT, Ngrids, Rbio)
              DO ng=1,Ngrids
                DO itrc=1,NBT
                  i=idbio(itrc)
                  ad_tnu2(i,ng)=Rbio(itrc,ng)
                  tl_tnu2(i,ng)=Rbio(itrc,ng)
                END DO
              END DO
            CASE ('ad_TNU4')
              Npts=load_r(Nval, Rval, NBT, Ngrids, Rbio)
              DO ng=1,Ngrids
                DO itrc=1,NBT
                  i=idbio(itrc)
                  ad_tnu4(i,ng)=Rbio(itrc,ng)
                  tl_tnu4(i,ng)=Rbio(itrc,ng)
                END DO
              END DO
            CASE ('LtracerSponge')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO itrc=1,NBT
                  i=idbio(itrc)
                  LtracerSponge(i,ng)=Ltrc(itrc,ng)
                END DO
              END DO
            CASE ('AKT_BAK')
              Npts=load_r(Nval, Rval, NBT, Ngrids, Rbio)
              DO ng=1,Ngrids
                DO itrc=1,NBT
                  i=idbio(itrc)
                  Akt_bak(i,ng)=Rbio(itrc,ng)
                END DO
              END DO
            CASE ('ad_AKT_fac')
              Npts=load_r(Nval, Rval, NBT, Ngrids, Rbio)
              DO ng=1,Ngrids
                DO itrc=1,NBT
                  i=idbio(itrc)
                  ad_Akt_fac(i,ng)=Rbio(itrc,ng)
                  tl_Akt_fac(i,ng)=Rbio(itrc,ng)
                END DO
              END DO
            CASE ('TNUDG')
              Npts=load_r(Nval, Rval, NBT, Ngrids, Rbio)
              DO ng=1,Ngrids
                DO itrc=1,NBT
                  i=idbio(itrc)
                  Tnudg(i,ng)=Rbio(itrc,ng)
                END DO
              END DO
            CASE ('Hadvection')
              IF (itracer.lt.NBT) THEN
                itracer=itracer+1
              ELSE
                itracer=1                      ! next nested grid
              END IF
              itrc=idbio(itracer)
              Npts=load_tadv(Nval, Cval, line, nline, itrc, igrid,      &
     &                       itracer, idbio(iTrcStr), idbio(iTrcEnd),   &
     &                       Vname(1,idTvar(itrc)),                     &
     &                       Hadvection)
            CASE ('Vadvection')
              IF (itracer.lt.NBT) THEN
                itracer=itracer+1
              ELSE
                itracer=1                      ! next nested grid
              END IF
              itrc=idbio(itracer)
              Npts=load_tadv(Nval, Cval, line, nline, itrc, igrid,      &
     &                       itracer, idbio(iTrcStr), idbio(iTrcEnd),   &
     &                       Vname(1,idTvar(itrc)),                     &
     &                       Vadvection)
#if defined ADJOINT || defined TANGENT || defined TL_IOMS
            CASE ('ad_Hadvection')
              IF (itracer.lt.NBT) THEN
                itracer=itracer+1
              ELSE
                itracer=1                      ! next nested grid
              END IF
              itrc=idbio(itracer)
              Npts=load_tadv(Nval, Cval, line, nline, itrc, igrid,      &
     &                       itracer, idbio(iTrcStr), idbio(iTrcEnd),   &
     &                       Vname(1,idTvar(itrc)),                     &
     &                       ad_Hadvection)
            CASE ('Vadvection')
              IF (itracer.lt.(NBT) THEN
                itracer=itracer+1
              ELSE
                itracer=1                      ! next nested grid
              END IF
              itrc=idbio(itracer)
              Npts=load_tadv(Nval, Cval, line, nline, itrc, igrid,      &
     &                       itracer, idbio(iTrcStr), idbio(iTrcEnd),   &
     &                       Vname(1,idTvar(itrc)),                     &
     &                       ad_Vadvection)
#endif
            CASE ('LBC(isTvar)')
              IF (itracer.lt.NBT) THEN
                itracer=itracer+1
              ELSE
                itracer=1                      ! next nested grid
              END IF
              ifield=isTvar(idbio(itracer))
              Npts=load_lbc(Nval, Cval, line, nline, ifield, igrid,     &
     &                      idbio(iTrcStr), idbio(iTrcEnd),             &
     &                      Vname(1,idTvar(idbio(itracer))), LBC)
#if defined ADJOINT || defined TANGENT || defined TL_IOMS
            CASE ('ad_LBC(isTvar)')
              IF (itracer.lt.NBT) THEN
                itracer=itracer+1
              ELSE
                itracer=1                      ! next nested grid
              END IF
              ifield=isTvar(idbio(itracer))
              Npts=load_lbc(Nval, Cval, line, nline, ifield, igrid,     &
     &                      idbio(iTrcStr), idbio(iTrcEnd),             &
     &                      Vname(1,idTvar(idbio(itracer))), ad_LBC)
#endif
            CASE ('LtracerSrc')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO itrc=1,NBT
                  i=idbio(itrc)
                  LtracerSrc(i,ng)=Ltrc(itrc,ng)
                END DO
              END DO
            CASE ('LtracerCLM')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO itrc=1,NBT
                  i=idbio(itrc)
                  LtracerCLM(i,ng)=Ltrc(itrc,ng)
                END DO
              END DO
            CASE ('LnudgeTCLM')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO itrc=1,NBT
                  i=idbio(itrc)
                  LnudgeTCLM(i,ng)=Ltrc(itrc,ng)
                END DO
              END DO
            CASE ('Hout(idTvar)')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO itrc=1,NBT
                  i=idTvar(idbio(itrc))
                  IF (i.eq.0) THEN
                    IF (Master) WRITE (out,30)                          &
     &                                'idTvar(idbio(', itrc, '))'
                    exit_flag=5
                    RETURN
                  END IF
                  Hout(i,ng)=Ltrc(itrc,ng)
                END DO
              END DO
            CASE ('Hout(idTsur)')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO itrc=1,NBT
                  i=idTsur(idbio(itrc))
                  IF (i.eq.0) THEN
                    IF (Master) WRITE (out,30)                          &
     &                                'idTsur(idbio(', itrc, '))'
                    exit_flag=5
                    RETURN
                  END IF
                  Hout(i,ng)=Ltrc(itrc,ng)
                END DO
              END DO
            CASE ('Qout(idTvar)')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO itrc=1,NBT
                  i=idTvar(idbio(itrc))
                  Qout(i,ng)=Ltrc(itrc,ng)
                END DO
              END DO
            CASE ('Qout(idsurT)')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO itrc=1,NBT
                  i=idsurT(idbio(itrc))
                  IF (i.eq.0) THEN
                    IF (Master) WRITE (out,30)                          &
     &                                'idsurT(idbio(', itrc, '))'
                    exit_flag=5
                    RETURN
                  END IF
                  Qout(i,ng)=Ltrc(itrc,ng)
                END DO
              END DO
            CASE ('Qout(idTsur)')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO itrc=1,NBT
                  i=idTsur(idbio(itrc))
                  Qout(i,ng)=Ltrc(itrc,ng)
                END DO
              END DO
#if defined AVERAGES    || \
   (defined AD_AVERAGES && defined ADJOINT) || \
   (defined RP_AVERAGES && defined TL_IOMS) || \
   (defined TL_AVERAGES && defined TANGENT)
            CASE ('Aout(idTvar)')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO itrc=1,NBT
                  i=idTvar(idbio(itrc))
                  Aout(i,ng)=Ltrc(itrc,ng)
                END DO
              END DO
            CASE ('Aout(idTTav)')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO itrc=1,NBT
                  i=idTTav(idbio(itrc))
                  Aout(i,ng)=Ltrc(itrc,ng)
                END DO
              END DO
            CASE ('Aout(idUTav)')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO itrc=1,NBT
                  i=idUTav(idbio(itrc))
                  Aout(i,ng)=Ltrc(itrc,ng)
                END DO
              END DO
            CASE ('Aout(idVTav)')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO itrc=1,NBT
                  i=idVTav(idbio(itrc))
                  Aout(i,ng)=Ltrc(itrc,ng)
                END DO
              END DO
            CASE ('Aout(iHUTav)')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO itrc=1,NBT
                  i=iHUTav(idbio(itrc))
                  Aout(i,ng)=Ltrc(itrc,ng)
                END DO
              END DO
            CASE ('Aout(iHVTav)')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO itrc=1,NBT
                  i=iHVTav(idbio(itrc))
                  Aout(i,ng)=Ltrc(itrc,ng)
                END DO
              END DO
#endif
#ifdef DIAGNOSTICS_TS
            CASE ('Dout(iTrate)')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO i=1,NBT
                  itrc=idbio(i)
                  Dout(idDtrc(itrc,iTrate),ng)=Ltrc(i,ng)
                END DO
              END DO
            CASE ('Dout(iThadv)')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO i=1,NBT
                  itrc=idbio(i)
                  Dout(idDtrc(itrc,iThadv),ng)=Ltrc(i,ng)
                END DO
              END DO
            CASE ('Dout(iTxadv)')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO i=1,NBT
                  itrc=idbio(i)
                  Dout(idDtrc(itrc,iTxadv),ng)=Ltrc(i,ng)
                END DO
              END DO
            CASE ('Dout(iTyadv)')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO i=1,NBT
                  itrc=idbio(i)
                  Dout(idDtrc(itrc,iTyadv),ng)=Ltrc(i,ng)
                END DO
              END DO
            CASE ('Dout(iTvadv)')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO i=1,NBT
                  itrc=idbio(i)
                  Dout(idDtrc(itrc,iTvadv),ng)=Ltrc(i,ng)
                END DO
              END DO
# if defined TS_DIF2 || defined TS_DIF4
            CASE ('Dout(iThdif)')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO i=1,NBT
                  itrc=idbio(i)
                  Dout(idDtrc(itrc,iThdif),ng)=Ltrc(i,ng)
                END DO
              END DO
            CASE ('Dout(iTxdif)')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO i=1,NBT
                  itrc=idbio(i)
                  Dout(idDtrc(itrc,iTxdif),ng)=Ltrc(i,ng)
                END DO
              END DO
            CASE ('Dout(iTydif)')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO i=1,NBT
                  itrc=idbio(i)
                  Dout(idDtrc(itrc,iTydif),ng)=Ltrc(i,ng)
                END DO
              END DO
#  if defined MIX_GEO_TS || defined MIX_ISO_TS
            CASE ('Dout(iTsdif)')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO i=1,NBT
                  itrc=idbio(i)
                  Dout(idDtrc(itrc,iTsdif),ng)=Ltrc(i,ng)
                END DO
              END DO
#  endif
# endif
            CASE ('Dout(iTvdif)')
              Npts=load_l(Nval, Cval, NBT, Ngrids, Ltrc)
              DO ng=1,Ngrids
                DO i=1,NBT
                  itrc=idbio(i)
                  Dout(idDtrc(itrc,iTvdif),ng)=Ltrc(i,ng)
                END DO
              END DO
#endif
#ifdef DIAGNOSTICS_BIO
# ifdef CARBON
            CASE ('Dout(iCOfx)')
              IF (iDbio2(iCOfx).eq.0) THEN
                IF (Master) WRITE (out,40) 'iDbio2(iCOfx)'
                exit_flag=5
                RETURN
              END IF
              Npts=load_l(Nval, Cval, Ngrids, Lbio)
              i=iDbio2(iCOfx)
              DO ng=1,Ngrids
                Dout(i,ng)=Lbio(ng)
              END DO
# endif
# ifdef DENITRIFICATION
            CASE ('Dout(iDNIT)')
              IF (iDbio2(iDNIT).eq.0) THEN
                IF (Master) WRITE (out,40) 'iDbio2(iDNIT)'
                exit_flag=5
                RETURN
              END IF
              Npts=load_l(Nval, Cval, Ngrids, Lbio)
              i=iDbio2(iDNIT)
              DO ng=1,Ngrids
                Dout(i,ng)=Lbio(ng)
              END DO
# endif
# ifdef CARBON
            CASE ('Dout(ipCO2)')
              IF (iDbio2(ipCO2).eq.0) THEN
                IF (Master) WRITE (out,40) 'iDbio2(ipCO2)'
                exit_flag=5
                RETURN
              END IF
              Npts=load_l(Nval, Cval, Ngrids, Lbio)
              i=iDbio2(ipCO2)
              DO ng=1,Ngrids
                Dout(i,ng)=Lbio(ng)
              END DO
# endif
# ifdef OXYGEN
            CASE ('Dout(iO2fx)')
              IF (iDbio2(iO2fx).eq.0) THEN
                IF (Master) WRITE (out,40) 'iDbio2(iO2fx)'
                exit_flag=5
                RETURN
              END IF
              Npts=load_l(Nval, Cval, Ngrids, Lbio)
              i=iDbio2(iO2fx)
              DO ng=1,Ngrids
                Dout(i,ng)=Lbio(ng)
              END DO
# endif
            CASE ('Dout(iPPro)')
              IF (iDbio3(iPPro).eq.0) THEN
                IF (Master) WRITE (out,40) 'iDbio3(iPPro)'
                exit_flag=5
                RETURN
              END IF
              Npts=load_l(Nval, Cval, Ngrids, Lbio)
              i=iDbio3(iPPro)
              DO ng=1,Ngrids
                Dout(i,ng)=Lbio(ng)
              END DO
            CASE ('Dout(iNO3u)')
              IF (iDbio3(iNO3u).eq.0) THEN
                IF (Master) WRITE (out,40) 'iDbio3(iNO3u)'
                exit_flag=5
                RETURN
              END IF
              Npts=load_l(Nval, Cval, Ngrids, Lbio)
              i=iDbio3(iNO3u)
              DO ng=1,Ngrids
                Dout(i,ng)=Lbio(ng)
              END DO
            CASE ('Dout(iNifx)')
              IF (iDbio3(iNifx).eq.0) THEN
                IF (Master) WRITE (out,40) 'iDbio3(iNifx)'
                exit_flag=5
                RETURN
              END IF
              Npts=load_l(Nval, Cval, Ngrids, Lbio)
              i=iDbio3(iNifx)
              DO ng=1,Ngrids
                Dout(i,ng)=Lbio(ng)
              END DO
#endif
          END SELECT
        END IF
      END DO
  10  IF (Master) WRITE (out,50) line
      exit_flag=4
      RETURN
  20  CONTINUE
!
!-----------------------------------------------------------------------
!  Report input parameters.
!-----------------------------------------------------------------------
!
      IF (Master.and.Lwrite) THEN
        DO ng=1,Ngrids
          IF (Lbiology(ng)) THEN
            WRITE (out,60) ng
            WRITE (out,70) BioIter(ng), 'BioIter',                      &
     &            'Number of iterations for nonlinear convergence.'
            WRITE (out,90) reg1(ng), 'reg1',                           &
     &            'Microzooplankton excretion rate to ammonium',        &
     &            '[1/day].'
            WRITE (out,80) reg2(ng), 'reg2',                           &
     &            'Mesozooplankton excretion rate to ammonium [1/day].'
            WRITE (out,90) gmaxs1(ng), 'gmaxs1',                       &
     &            'Maximum specific growth rate of small phytoplankton',&
     &            '[1/day].'
            WRITE (out,80) gmaxs2(ng), 'gmaxs2',                       &
     &            'Maximum specific growth rate of diatom [1/day].'
            WRITE (out,80) gmaxs3(ng), 'gmaxs3',                       &
     &            'Maximum specific growth rate of coccolith [1/day].'
            WRITE (out,80) beta1(ng), 'beta1',                         &
     &            'Microzooplankton maximum grazing rate [1/day].'
            WRITE (out,80) beta2(ng), 'beta2',                         &
     &            'Mesozooplankton maximum grazing rate [1/day].'
            WRITE (out,90) akz1(ng), 'akz1',                           &
     &            'Half saturation constant for microzooplankton',      &
     &            'grazing [mmol_N/m3].'
            WRITE (out,90) akz2(ng), 'akz2',                           &
     &            'Half saturation constant for mesozooplankton',       &
     &            'grazing [mmol_N/m3].'
            WRITE (out,90) PARfrac(ng), 'PARfrac',                     &
     &            'Fraction of shortwave radiation that is',            &
     &            'photosynthetically active (nondimensional).'
            WRITE (out,90) alphachl_s1(ng), 'alphachl_s1',             &
     &            'Initial chl-specific slope of P-I curve of small',   &
     &            'phytoplankton [molC m2/(gChl Watts day)].'
            WRITE (out,90) alphachl_s2(ng), 'alphachl_s2',             &
     &            'Initial chl-specific slope of P-I curve of diatom',  &
     &            '[molC m2/(gChl Watts day)].'
            WRITE (out,90) alphachl_s3(ng), 'alphachl_s3',             &
     &            'Initial chl-specific slope of P-I curve of ',        &
     &            'coccolithophores [molC m2/(gChl Watts day)].'
            WRITE (out,90) pis1(ng), 'pis1',                           &
     &            'Ammonium inhibition parameter for small',            &
     &            'phytoplankton [mmol_N/m3].'
            WRITE (out,90) pis2(ng), 'pis2',                           &
     &            'Ammonium inhibition parameter for diatom',           &
     &            '[mmol_N/m3].'
            WRITE (out,90) pis3(ng), 'pis3',                           &
     &            'Ammonium inhibition parameter for ',                 &
     &            'coccolithophores [mmol_N/m3].'
            WRITE (out,90) akno3s1(ng), 'akno3s1',                     &
     &            'Half saturation concentration for nitrate',          &
     &            'uptake by small phytoplankton [mmol_N/m3].'
            WRITE (out,90) akno3s2(ng), 'akno3s2',                     &
     &            'Half saturation concentration for nitrate',          &
     &            'uptake by diatom [mmol_N/m3].'
            WRITE (out,90) akno3s3(ng), 'akno3s3',                     &
     &            'Half saturation concentration for nitrate',          &
     &            'uptake by coccolithophores [mmol_N/m3].'
            WRITE (out,90) aknh4s1(ng), 'aknh4s1',                     &
     &            'Half saturation concentration for ammonium',         &
     &            'uptake by small phytoplankton [mmol_N/m3].'
            WRITE (out,90) aknh4s2(ng), 'aknh4s2',                     &
     &            'Half saturation concentration for ammonium',         &
     &            'uptake by diatom [mmol_N/m3].'
            WRITE (out,90) aknh4s3(ng), 'aknh4s3',                     &
     &            'Half saturation concentration for ammonium',         &
     &            'uptake by coccolithophores [mmol_N/m3].'
            WRITE (out,90) akpo4s1(ng), 'akpo4s1',                     &
     &            'Half saturation concentration for phosphate',        &
     &            'uptake by small phytoplankton [mmol_P/m3].'
            WRITE (out,90) akpo4s2(ng), 'akpo4s2',                     &
     &            'Half saturation concentration for phosphate',        &
     &            'uptake by diatom [mmol_P/m3].'
            WRITE (out,90) akpo4s3(ng), 'akpo4s3',                     &
     &            'Half saturation concentration for phosphate',        &
     &            'uptake by coccolithophores [mmol_P/m3].'
            WRITE (out,90) akco2s1(ng), 'akco2s1',                     &
     &            'Half saturation concentration for co2',              &
     &            'uptake by small phytoplankton [mmol_C/m3].'
            WRITE (out,90) akco2s2(ng), 'akco2s2',                     &
     &            'Half saturation concentration for co2',              &
     &            'uptake by diatom [mmol_C/m3].'
            WRITE (out,90) akco2s3(ng), 'akco2s3',                     &
     &            'Half saturation concentration for co2',              &
     &            'uptake by coccolithophores [mmol_C/m3].'
            WRITE (out,90) aksio4s2(ng), 'aksio4s2',                   &
     &            'Half saturation constant for silicate',              &
     &            'uptake by diatom [mmol_N/m3].'
            WRITE (out,90) ES1(ng), 'ES1',                             &
     &            'Phytoplankton exudation parameter for',              &
     &            'small phytoplankton [nondimensional].'
            WRITE (out,90) ES2(ng), 'ES2',                             &
     &            'Phytoplankton exudation parameter for',              &
     &            'diatom [nondimensional].'
            WRITE (out,90) ES3(ng), 'ES3',                             &
     &            'Phytoplankton exudation parameter for',              &
     &            'coccolithophores [nondimensional].'
            WRITE (out,80) ak1(ng), 'ak1',                             &
     &            'Light attenuation coefficient of water [1/m].'
            WRITE (out,90) ak2(ng), 'ak2',                             &
     &            'Specific light attenuation coefficient for',         &
     &            'phytoplankton [1/m/(mmol_N/m3)].'
            WRITE (out,80) Qmax(ng), 'Qmax',                           &
     &            'Maximum phytoplankton N:C ratio [molN/molC].'
            WRITE (out,80) Qmin(ng), 'Qmin',                           &
     &            'Minimum phytoplankton N:C ratio [molN/molC].'
            WRITE (out,90) lambdano3_s1(ng), 'lambdano3_s1',           &
     &            'Cost of biosynthesis for',                           &
     &            'small phytoplankton [molC/molN].'
            WRITE (out,90) lambdano3_s2(ng), 'lambdano3_s2',           &
     &            'Cost of biosynthesis for',                           &
     &            'diatom [molC/molN].'
            WRITE (out,90) lambdano3_s3(ng), 'lambdano3_s3',           &
     &            'Cost of biosynthesis for',                           &
     &            'coccolithophores [molC/molN].'
            WRITE (out,80) thetaNmax_s1(ng), 'thetaNmax_s1',           &
     &            'Maximum Chl:N for small phytoplankton [gChl/molN].'
            WRITE (out,80) thetaNmax_s2(ng), 'thetaNmax_s2',           &
     &            'Maximum Chl:N for diatom [gChl/molN].'
            WRITE (out,80) thetaNmax_s3(ng), 'thetaNmax_s3',           &
     &            'Maximum Chl:N for coccolithophores [gChl/molN].'
            WRITE (out,80) bgamma(ng), 'bgamma',                       &
     &            'Mesozooplankton specific mortality rate [1/day].'
            WRITE (out,90) bgamma1(ng), 'bgamma1',                     &
     &            'Grazing efficiency of microzooplankton',             &
     &            '[nondimensional].'
            WRITE (out,90) bgamma2(ng), 'bgamma2',                     &
     &            ' Grazing efficiency of mesozooplankton for N',       &
     &            '[nondimensional].'
            WRITE (out,90) bgamma22(ng), 'bgamma22',                   &
     &            ' Grazing efficiency of mesozooplankton for C',       &
     &            '[nondimensional].'
            WRITE (out,80) bgamma3(ng), 'bgamma3',                     &
     &            'Death rate of small phytoplankton [1/day].'
            WRITE (out,80) bgamma4(ng), 'bgamma4',                     &
     &            'Death rate of large phytoplankton [1/day].'
            WRITE (out,80) bgamma10(ng), 'bgamma10',                   &
     &            'Death rate of coccolithophores [1/day].'
            WRITE (out,80) bgamma12(ng), 'bgamma12',                   &
     &            'Death rate of bacteria [1/day].'
            WRITE (out,80) bgamma5(ng), 'bgamma5',                     &
     &            'Decay rate of detritus [1/day].'
            WRITE (out,80) bgamma7(ng), 'bgamma7',                     &
     &            'Nitrafication rate [1/day].'
            WRITE (out,80) bgamma11(ng), 'bgamma11',                   &
     &            'Maximum ammonium uptake rate by bacteria [1/day].'
            WRITE (out,80) bgamma13(ng), 'bgamma13',                   &
     &            'Maximum semi-labile hydrolysis [1/day].'
            WRITE (out,90) mtos1(ng), 'mtos1',                         &
     &            'Ratio of mortality to dissolved pool of',            &
     &            'small phytoplankton [nondimensional].'
            WRITE (out,90) mtos2(ng), 'mtos2',                         &
     &            'Ratio of mortality to dissolved pool of',            &
     &            'diatom [nondimensional].'
            WRITE (out,90) mtos3(ng), 'mtos3',                         &
     &            'Ratio of mortality to dissolved pool of',            &
     &            'coccolithophores [nondimensional].'
            WRITE (out,80) flz1(ng), 'flz1',                           &
     &            'Feeding loss by small zooplankton [nondimensional].'
            WRITE (out,80) flz2(ng), 'flz2',                           &
     &            'Feeding loss by large zooplankton [nondimensional].'
            WRITE (out,90) lk1(ng), 'lk1',                             &
     &            'Phytoplankton leakage fraction of',                  &
     &            ' small phytoplankton [nondimensional].'
            WRITE (out,90) lk2(ng), 'lk2',                             &
     &            'Phytoplankton leakage fraction of',                  &
     &            ' diatom [nondimensional].'
            WRITE (out,90) lk3(ng), 'lk3',                             &
     &            'Phytoplankton leakage fraction of',                  &
     &            ' coccolithophores [nondimensional].'
            WRITE (out,80) ratiol1(ng), 'ratiol1',                     &
     &            'Labile fraction [nondimensional].'
            WRITE (out,80) ratiol2(ng), 'ratiol2',                     &
     &            'Labile fraction for phytoplankton [nondimensional].'
            WRITE (out,80) wsdn(ng), 'wsdn',                           &
     &            'Sinking velocity of detritus N [m/day].'
            WRITE (out,80) wsdc(ng), 'wsdc',                           &
     &            'Sinking velocity of detritus C [m/day].'
            WRITE (out,80) wsdsi(ng), 'wsdsi',                         &
     &            'Sinking velocity of detritus silicate [m/day].'
            WRITE (out,80) wsdca(ng), 'wsdca',                         &
     &            'Sinking velocity of PIC [m/day].'
            WRITE (out,80) wsp1(ng), 'wsp1',                           &
     &            'Sinking velocity of small phytoplankton [m/day].'
            WRITE (out,80) wsp2(ng), 'wsp2',                           &
     &            'Sinking velocity of diatom [m/day].'
            WRITE (out,80) wsp3(ng), 'wsp3',                           &
     &            'Sinking velocity of coccolithophores [m/day].'
            WRITE (out,80) pco2a(ng), 'pco2a',                         &
     &            'Air pCO2 [ppmv].'
            WRITE (out,80) p2n(ng), 'p2n',                             &
     &            'Phosphorus to nitrogen ratio [mol_P/mol_N].'
            WRITE (out,80) o2no(ng), 'o2no',                           &
     &            'Oxygen to nitrate ratio [mol_O2/mol_NO3].'
            WRITE (out,80) o2nh(ng), 'o2nh',                           &
     &            'Oxygen to ammonium ratio [mol_O2/mol_NH4].'
            WRITE (out,80) cnb(ng), 'cnb',                             &
     &            'C:N in bacteria [molC/molN].'
            WRITE (out,80) apsilon(ng), 'apsilon',                     &
     & 'Ratio of PIC to organic carbon in coccolithophores [molC/molN].'
            WRITE (out,80) ro5(ng), 'ro5',                             &
     &            'Grazing preference for diatom [nondimensional].'
            WRITE (out,90) ro6(ng), 'ro6',                             &
     &            'Grazing preference for mesozooplankton',             &
     &            '[nondimensional].'
            WRITE (out,80) ro7(ng), 'ro7',                             &
     &            'Grazing preference for detritus [nondimensional].'
            WRITE (out,80) ro10(ng), 'ro10',                           &
     &       'Grazing preference for coccolithophores [nondimensional].'
            WRITE (out,80) rop(ng), 'rop',                             &
     &    'Grazing preference for small phytoplankton [nondimensional].'
            WRITE (out,80) rob(ng), 'rob',                             &
     &    'Grazing preference for bacteria [nondimensional].'
            WRITE (out,80) kabac(ng), 'kabac',                         &
     &    'Half saturation for ammonium uptake by bacteria [mmolN/m3].'
            WRITE (out,80) klbac(ng), 'klbac',                         &
     &               'Half saturation for labile DOC uptake [mmolC/m3].'
            WRITE (out,80) ksdoc(ng), 'ksdoc',                         &
     &          'Half saturation for semi-labile DOC uptake [mmolC/m3].'
            WRITE (out,80) ksdon(ng), 'ksdon',                         &
     &          'Half saturation for semi-labile DON uptake [mmolN/m3].'
            WRITE (out,80) ratiob(ng), 'ratiob',                       &
     &          'Bacteria growth loss fraction [nondimensional].'
            WRITE (out,80) ratiobc(ng), 'ratiobc',                     &
     &          'Color fraction of Bacteria loss [nondimensional].'
            WRITE (out,90) RtUVLDOC(ng), 'RtUVLDOC',                   &
     &        'Rate of conversion of colored labile DOC to labile DOC', &
     &        ' [mmolC/m2/d].'
            WRITE (out,90) RtUVSDOC(ng), 'RtUVSDOC',                   &
     &        'Rate of conversion of colored semi-labile DOC to',       &
     &        ' labile DOC [mmolC/m2/d].'
            WRITE (out,90) RtUVLDIC(ng), 'RtUVLDIC',                   &
     &        'Rate of conversion of colored labile DOC to DIC',        &
     &        ' [mmolC/m2/d].'
            WRITE (out,90) RtUVSDIC(ng), 'RtUVSDIC',                   &
     &        'Rate of conversion of colored semi-labile DOC to DIC',   &
     &        ' [mmolC/m2/d].'
            WRITE (out,80) colorFR1(ng), 'colorFR1',                   &
     &            'Color fraction for labile DOC [nondimensional].'
            WRITE (out,80) colorFR2(ng), 'colorFR2',                   &
     &           'Color fraction for semi-labile DOC [nondimensional].'
#ifdef IRON_LIMIT
            WRITE (out,140) T_Fe(ng), 'T_Fe',                            &
     &            'Iron uptake time scale (day-1).'
            WRITE (out,140) A_Fe(ng), 'A_Fe',                            &
     &            'Empirical Fe:C power (-).'
            WRITE (out,140) B_Fe(ng), 'B_Fe',                            &
     &            'Empirical Fe:C coefficient (1/M-C).'
            WRITE (out,140) S1_FeC(ng), 'S1_FeC',                        &
     &            'Small P Fe:C at F=0.5 (muM-Fe/M-C).'
            WRITE (out,140) S2_FeC(ng), 'S2_FeC',                        &
     &            'Diatoms Fe:C at F=0.5 (muM-Fe/M-C).'
            WRITE (out,140) S3_FeC(ng), 'S3_FeC',                        &
     &            'Coccolithophores Fe:C at F=0.5 (muM-Fe/M-C).'
            WRITE (out,140) FeRR(ng), 'FeRR',                            &
     &            'Fe remineralization rate (day-1).'
#endif
#ifdef TS_DIF2
            DO itrc=1,NBT
              i=idbio(itrc)
              WRITE (out,100) nl_tnu2(i,ng), 'nl_tnu2', i,              &
     &              'NLM Horizontal, harmonic mixing coefficient',      &
     &              '(m2/s) for tracer ', i, TRIM(Vname(1,idTvar(i)))
# ifdef ADJOINT
              WRITE (out,100) ad_tnu2(i,ng), 'ad_tnu2', i,              &
     &              'ADM Horizontal, harmonic mixing coefficient',      &
     &              '(m2/s) for tracer ', i, TRIM(Vname(1,idTvar(i)))
# endif
# if defined TANGENT || defined TL_IOMS
              WRITE (out,100) tl_tnu2(i,ng), 'tl_tnu2', i,              &
     &              'TLM Horizontal, harmonic mixing coefficient',      &
     &              '(m2/s) for tracer ', i, TRIM(Vname(1,idTvar(i)))
# endif
            END DO
#endif
#ifdef TS_DIF4
            DO itrc=1,NBT
              i=idbio(itrc)
              WRITE (out,100) nl_tnu4(i,ng), 'nl_tnu4', i,              &
     &              'NLM Horizontal, biharmonic mixing coefficient',    &
     &              '(m4/s) for tracer ', i, TRIM(Vname(1,idTvar(i)))
# ifdef ADJOINT
              WRITE (out,100) ad_tnu4(i,ng), 'ad_tnu4', i,              &
     &              'ADM Horizontal, biharmonic mixing coefficient',    &
     &              '(m4/s) for tracer ', i, TRIM(Vname(1,idTvar(i)))
# endif
# if defined TANGENT || defined TL_IOMS
              WRITE (out,100) tl_tnu4(i,ng), 'tl_tnu4', i,              &
     &              'TLM Horizontal, biharmonic mixing coefficient',    &
     &              '(m4/s) for tracer ', i, TRIM(Vname(1,idTvar(i)))
# endif
            END DO
#endif
            DO itrc=1,NBT
              i=idbio(itrc)
              IF (LtracerSponge(i,ng)) THEN
                WRITE (out,110) LtracerSponge(i,ng), 'LtracerSponge',   &
     &              i, 'Turning ON  sponge on tracer ', i,              &
     &              TRIM(Vname(1,idTvar(i)))
              ELSE
                WRITE (out,110) LtracerSponge(i,ng), 'LtracerSponge',   &
     &              i, 'Turning OFF sponge on tracer ', i,              &
     &              TRIM(Vname(1,idTvar(i)))
              END IF
            END DO
            DO itrc=1,NBT
              i=idbio(itrc)
              WRITE(out,100) Akt_bak(i,ng), 'Akt_bak', i,               &
     &             'Background vertical mixing coefficient (m2/s)',     &
     &             'for tracer ', i, TRIM(Vname(1,idTvar(i)))
            END DO
#ifdef FORWARD_MIXING
            DO itrc=1,NBT
              i=idbio(itrc)
# ifdef ADJOINT
              WRITE (out,100) ad_Akt_fac(i,ng), 'ad_Akt_fac', i,        &
     &              'ADM basic state vertical mixing scale factor',     &
     &              'for tracer ', i, TRIM(Vname(1,idTvar(i)))
# endif
# if defined TANGENT || defined TL_IOMS
              WRITE (out,100) tl_Akt_fac(i,ng), 'tl_Akt_fac', i,        &
     &              'TLM basic state vertical mixing scale factor',     &
     &              'for tracer ', i, TRIM(Vname(1,idTvar(i)))
# endif
            END DO
#endif
            DO itrc=1,NBT
              i=idbio(itrc)
              WRITE (out,100) Tnudg(i,ng), 'Tnudg', i,                  &
     &              'Nudging/relaxation time scale (days)',             &
     &              'for tracer ', i, TRIM(Vname(1,idTvar(i)))
            END DO
            DO itrc=1,NBT
              i=idbio(itrc)
              IF (LtracerSrc(i,ng)) THEN
                WRITE (out,110) LtracerSrc(i,ng), 'LtracerSrc',         &
     &              i, 'Turning ON  point sources/Sink on tracer ', i,  &
     &              TRIM(Vname(1,idTvar(i)))
              ELSE
                WRITE (out,110) LtracerSrc(i,ng), 'LtracerSrc',         &
     &              i, 'Turning OFF point sources/Sink on tracer ', i,  &
     &              TRIM(Vname(1,idTvar(i)))
              END IF
            END DO
            DO itrc=1,NBT
              i=idbio(itrc)
              IF (LtracerCLM(i,ng)) THEN
                WRITE (out,110) LtracerCLM(i,ng), 'LtracerCLM', i,      &
     &              'Turning ON  processing of climatology tracer ', i, &
     &              TRIM(Vname(1,idTvar(i)))
              ELSE
                WRITE (out,110) LtracerCLM(i,ng), 'LtracerCLM', i,      &
     &              'Turning OFF processing of climatology tracer ', i, &
     &              TRIM(Vname(1,idTvar(i)))
              END IF
            END DO
            DO itrc=1,NBT
              i=idbio(itrc)
              IF (LnudgeTCLM(i,ng)) THEN
                WRITE (out,110) LnudgeTCLM(i,ng), 'LnudgeTCLM', i,      &
     &              'Turning ON  nudging of climatology tracer ', i,    &
     &              TRIM(Vname(1,idTvar(i)))
              ELSE
                WRITE (out,110) LnudgeTCLM(i,ng), 'LnudgeTCLM', i,      &
     &              'Turning OFF nudging of climatology tracer ', i,    &
     &              TRIM(Vname(1,idTvar(i)))
              END IF
            END DO
            IF ((nHIS(ng).gt.0).and.ANY(Hout(:,ng))) THEN
              WRITE (out,'(1x)')
              DO itrc=1,NBT
                i=idbio(itrc)
                IF (Hout(idTvar(i),ng)) WRITE (out,120)                 &
     &              Hout(idTvar(i),ng), 'Hout(idTvar)',                 &
     &              'Write out tracer ', i, TRIM(Vname(1,idTvar(i)))
              END DO
              DO itrc=1,NBT
                i=idbio(itrc)
                IF (Hout(idTsur(i),ng)) WRITE (out,120)                 &
     &              Hout(idTsur(i),ng), 'Hout(idTsur)',                 &
     &              'Write out tracer flux ', i,                        &
     &              TRIM(Vname(1,idTvar(i)))
              END DO
            END IF
            IF ((nQCK(ng).gt.0).and.ANY(Qout(:,ng))) THEN
              WRITE (out,'(1x)')
              DO itrc=1,NBT
                i=idbio(itrc)
                IF (Qout(idTvar(i),ng)) WRITE (out,120)                 &
     &              Qout(idTvar(i),ng), 'Qout(idTvar)',                 &
     &              'Write out tracer ', i, TRIM(Vname(1,idTvar(i)))
              END DO
              DO itrc=1,NBT
                i=idbio(itrc)
                IF (Qout(idsurT(i),ng)) WRITE (out,120)                 &
     &              Qout(idsurT(i),ng), 'Qout(idsurT)',                 &
     &              'Write out surface tracer ', i,                     &
     &              TRIM(Vname(1,idTvar(i)))
              END DO
              DO itrc=1,NBT
                i=idbio(itrc)
                IF (Qout(idTsur(i),ng)) WRITE (out,120)                 &
     &              Qout(idTsur(i),ng), 'Qout(idTsur)',                 &
     &              'Write out tracer flux ', i,                        &
     &              TRIM(Vname(1,idTvar(i)))
              END DO
            END IF
#if defined AVERAGES    || \
   (defined AD_AVERAGES && defined ADJOINT) || \
   (defined RP_AVERAGES && defined TL_IOMS) || \
   (defined TL_AVERAGES && defined TANGENT)
            IF ((nAVG(ng).gt.0).and.ANY(Aout(:,ng))) THEN
              WRITE (out,'(1x)')
              DO itrc=1,NBT
                i=idbio(itrc)
                IF (Aout(idTvar(i),ng)) WRITE (out,120)                 &
     &              Aout(idTvar(i),ng), 'Aout(idTvar)',                 &
     &              'Write out averaged tracer ', i,                    &
     &              TRIM(Vname(1,idTvar(i)))
              END DO
              DO itrc=1,NBT
                i=idbio(itrc)
                IF (Aout(idTTav(i),ng)) WRITE (out,120)                 &
     &              Aout(idTTav(i),ng), 'Aout(idTTav)',                 &
     &              'Write out averaged <t*t> for tracer ', i,          &
     &              TRIM(Vname(1,idTvar(i)))
              END DO
              DO itrc=1,NBT
                i=idbio(itrc)
                IF (Aout(idUTav(i),ng)) WRITE (out,120)                 &
     &              Aout(idUTav(i),ng), 'Aout(idUTav)',                 &
     &              'Write out averaged <u*t> for tracer ', i,          &
     &              TRIM(Vname(1,idTvar(i)))
              END DO
              DO itrc=1,NBT
                i=idbio(itrc)
                IF (Aout(idVTav(i),ng)) WRITE (out,120)                 &
     &              Aout(idVTav(i),ng), 'Aout(idVTav)',                 &
     &              'Write out averaged <v*t> for tracer ', i,          &
     &              TRIM(Vname(1,idTvar(i)))
              END DO
              DO itrc=1,NBT
                i=idbio(itrc)
                IF (Aout(iHUTav(i),ng)) WRITE (out,120)                 &
     &              Aout(iHUTav(i),ng), 'Aout(iHUTav)',                 &
     &              'Write out averaged <Huon*t> for tracer ', i,       &
     &              TRIM(Vname(1,idTvar(i)))
              END DO
              DO itrc=1,NBT
                i=idbio(itrc)
                IF (Aout(iHVTav(i),ng)) WRITE (out,120)                 &
     &              Aout(iHVTav(i),ng), 'Aout(iHVTav)',                 &
     &              'Write out averaged <Hvom*t> for tracer ', i,       &
     &              TRIM(Vname(1,idTvar(i)))
              END DO
            END IF
#endif
#ifdef DIAGNOSTICS_TS
            IF ((nDIA(ng).gt.0).and.ANY(Dout(:,ng))) THEN
              WRITE (out,'(1x)')
              DO i=1,NBT
                itrc=idbio(i)
                IF (Dout(idDtrc(itrc,iTrate),ng))                       &
     &            WRITE (out,120) .TRUE., 'Dout(iTrate)',               &
     &                'Write out rate of change of tracer ', itrc,      &
     &                TRIM(Vname(1,idTvar(itrc)))
              END DO
              DO i=1,NBT
                itrc=idbio(i)
                IF (Dout(idDtrc(itrc,iThadv),ng))                       &
     &            WRITE (out,120) .TRUE., 'Dout(iThadv)',               &
     &                'Write out horizontal advection, tracer ', itrc,  &
     &                TRIM(Vname(1,idTvar(itrc)))
              END DO
              DO i=1,NBT
                itrc=idbio(i)
                IF (Dout(idDtrc(itrc,iTxadv),ng))                       &
     &            WRITE (out,120) .TRUE., 'Dout(iTxadv)',               &
     &               'Write out horizontal X-advection, tracer ', itrc, &
     &               TRIM(Vname(1,idTvar(itrc)))
              END DO
              DO i=1,NBT
                itrc=idbio(i)
                IF (Dout(idDtrc(itrc,iTyadv),ng))                       &
     &            WRITE (out,120) .TRUE., 'Dout(iTyadv)',               &
     &               'Write out horizontal Y-advection, tracer ', itrc, &
     &               TRIM(Vname(1,idTvar(itrc)))
              END DO
              DO i=1,NBT
                itrc=idbio(i)
                IF (Dout(idDtrc(itrc,iTvadv),ng))                       &
     &            WRITE (out,120) .TRUE., 'Dout(iTvadv)',               &
     &                'Write out vertical advection, tracer ', itrc,    &
     &                TRIM(Vname(1,idTvar(itrc)))
              END DO
# if defined TS_DIF2 || defined TS_DIF4
              DO i=1,NBT
                itrc=idbio(i)
                IF (Dout(idDtrc(itrc,iThdif),ng))                       &
     &            WRITE (out,120) .TRUE., 'Dout(iThdif)',               &
     &                'Write out horizontal diffusion, tracer ', itrc,  &
     &                TRIM(Vname(1,idTvar(itrc)))
              END DO
              DO i=1,NBT
                itrc=idbio(i)
                IF (Dout(idDtrc(i,iTxdif),ng))                          &
     &            WRITE (out,120) .TRUE., 'Dout(iTxdif)',               &
     &               'Write out horizontal X-diffusion, tracer ', itrc, &
     &               TRIM(Vname(1,idTvar(itrc)))
              END DO
              DO i=1,NBT
                itrc=idbio(i)
                IF (Dout(idDtrc(itrc,iTydif),ng))                       &
     &            WRITE (out,120) .TRUE., 'Dout(iTydif)',               &
     &               'Write out horizontal Y-diffusion, tracer ', itrc, &
     &               TRIM(Vname(1,idTvar(itrc)))
              END DO
#  if defined MIX_GEO_TS || defined MIX_ISO_TS
              DO i=1,NBT
                itrc=idbio(i)
                IF (Dout(idDtrc(itrc,iTsdif),ng))                       &
     &            WRITE (out,120) .TRUE., 'Dout(iTsdif)',               &
     &               'Write out horizontal S-diffusion, tracer ', itrc, &
     &               TRIM(Vname(1,idTvar(itrc)))
              END DO
#  endif
# endif
              DO i=1,NBT
                itrc=idbio(i)
                IF (Dout(idDtrc(itrc,iTvdif),ng))                       &
     &            WRITE (out,120) .TRUE., 'Dout(iTvdif)',               &
     &                'Write out vertical diffusion, tracer ', itrc,    &
     &                TRIM(Vname(1,idTvar(itrc)))
              END DO
            END IF
#endif
#ifdef DIAGNOSTICS_BIO
            IF (nDIA(ng).gt.0) THEN
              IF (NDbio2d.gt.0) THEN
                DO itrc=1,NDbio2d
                  i=iDbio2(itrc)
                  IF (Dout(i,ng)) WRITE (out,130)                       &
     &                Dout(i,ng), 'Dout(iDbio2)',                       &
     &                'Write out diagnostics for', TRIM(Vname(1,i))
                END DO
              END IF
              DO itrc=1,NDbio3d
                i=iDbio3(itrc)
                IF (Dout(i,ng)) WRITE (out,130)                         &
     &              Dout(i,ng), 'Dout(iDbio3)',                         &
     &              'Write out diagnostics for', TRIM(Vname(1,i))
              END DO
            END IF
#endif
          END IF
        END DO
      END IF
!
!-----------------------------------------------------------------------
!  Rescale biological tracer parameters.
!-----------------------------------------------------------------------
!
!  Take the square root of the biharmonic coefficients so it can
!  be applied to each harmonic operator.
!
      DO ng=1,Ngrids
        DO itrc=1,NBT
          i=idbio(itrc)
          nl_tnu4(i,ng)=SQRT(ABS(nl_tnu4(i,ng)))
#ifdef ADJOINT
          ad_tnu4(i,ng)=SQRT(ABS(ad_tnu4(i,ng)))
#endif
#if defined TANGENT || defined TL_IOMS
          tl_tnu4(i,ng)=SQRT(ABS(tl_tnu4(i,ng)))
#endif
!
!  Compute inverse nudging coefficients (1/s) used in various tasks.
!
          IF (Tnudg(i,ng).gt.0.0_r8) THEN
            Tnudg(i,ng)=1.0_r8/(Tnudg(i,ng)*86400.0_r8)
          ELSE
            Tnudg(i,ng)=0.0_r8
          END IF
        END DO
      END DO

!   30  FORMAT (/,' read_BioPar - Error while processing line: ',/,a)
!   40  FORMAT (/,/,' UMaine CoSiNE Model Parameters, Grid: ',i2.2,       &
!      &        /,  ' =================================',/)
!   50  FORMAT (1x,i10,2x,a,t30,a)
!   60  FORMAT (10x,l1,2x,a,t30,a,i2.2,':',1x,a)
!   70  FORMAT (f11.3,2x,a,t30,a)
!   80  FORMAT (f11.3,2x,a,t30,a,/,t32,a)
!   90  FORMAT (1p,e11.4,2x,a,'(',i2.2,')',t30,a,/,t32,a,i2.2,':',1x,a)
!  100  FORMAT (1p,e11.4,2x,a,t30,a)
!  110  FORMAT (1p,e11.4,2x,a,t30,a,/,t32,a)
!  120  FORMAT (/,' read_BioPar - variable info not yet loaded, ',        &
!      &        a,i2.2,a)
!  130  FORMAT (/,' read_BioPar - variable info not yet loaded, ',a)
!  140  FORMAT (10x,l1,2x,a,t30,a,1x,a)
!  150  FORMAT (10x,l1,2x,a,'(',i2.2,')',t30,a,i2.2,':',1x,a)
      30  FORMAT (/,' read_BioPar - variable info not yet loaded, ',        &
      &        a,i2.2,a)
   40  FORMAT (/,' read_BioPar - variable info not yet loaded, ',a)
   50  FORMAT (/,' read_BioPar - Error while processing line: ',/,a)
   60  FORMAT (/,/,' Fennel Model Parameters, Grid: ',i2.2,              &
      &        /,  ' =================================',/)
   70  FORMAT (1x,i10,2x,a,t32,a)
   80  FORMAT (1p,e11.4,2x,a,t32,a)
   90  FORMAT (1p,e11.4,2x,a,t32,a,/,t34,a)
  100  FORMAT (1p,e11.4,2x,a,'(',i2.2,')',t32,a,/,t34,a,i2.2,':',1x,a)
  110  FORMAT (10x,l1,2x,a,'(',i2.2,')',t32,a,i2.2,':',1x,a)
  120  FORMAT (10x,l1,2x,a,t32,a,i2.2,':',1x,a)
  130  FORMAT (10x,l1,2x,a,t32,a,1x,a)
  140  FORMAT (f11.3,2x,a,t30,a)

      RETURN
      END SUBROUTINE read_BioPar
