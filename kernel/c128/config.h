;// main configuration file

#ifndef _CONFIG_H
#define _CONFIG_H

# define C128
# define MACHINE_H <c128.h>
# define MACHINE(file) "c128/file"

;// Keyboard/console settings
;// -------------------------
;//   LUnix uses the UNIX ascii scheme, if you want to use the old petscii
;//   scheme add the next line (saves 11 bytes)
;//   NOTE: this will break most of the applications!

;#define PETSCII


;// Kernel error messages
;// ---------------------
;//   The functions "lkf_printerror" and "lkf_suicerrout" print a short
;//   message via printk. Normally just the error code is reported.
;//   If you want to have textual error messages add the following to
;//   the compile-flags (costs 444 bytes)

#define VERBOSE_ERROR


;// Commodore IEC serial bus messages
;// ---------------------------------
;//
;//   After opening files and after other disc operations the IEC error 
;//   channel (secundary address 15) is read out. If "PRINT_IECMSG" is defined
;//   all messages other than ("00 OK ...") will be reported via printk.
;//   (costs 37 bytes)

;#define PRINT_IECMSG


;// REU support
;// -----------
;// if you have a REU installed at $df00 you may define the following
;// the use of REU's DMA feature will speed up several things, but may also
;// lead to problems with applications that require short NMI/IRQ latencies.
;// The REU kernel is around 102 bytes smaller than the normal one,
;// because HAVE_REU also implies ALWAYS_SZU.

;#define HAVE_REU

;// 256k expansion support
;// ----------------------
;// define this if you have C128 ram expanded to 256k (as described by Marko Makela)
;// currently it gives you nothing, but little fix in tasksw.s
;// please e-mail me (ytm@friko.onet.pl) and tell me if Lunix runs on your
;// expanded C128 with and without this definition
;// (on mine it refuses to work without it)

;#define HAVE_256K

;// VDC console
;// -----------
;// if you run LUnix on a C128 in C64 mode, you might want to use
;// the 80 column capabillities of the VDC instead of the standard
;// VIC-text console.
;// (this replaces the VIC console and implies multiple consoles plus
;// use of the 2MHz mode of the C128)
;// saves 2048-131=1917 bytes compared with (VIC/Multiple Consoles)

#define VDC_CONSOLE

;// Multiple consoles
;// -----------------
;// startup with more than just one console, system needs at least 1k for
;// each additional console! (should better allocate memory on demand)
;// currently the functions keys are used to select and shift+commodore to
;// switch between consoles (this time just 2 consoles are available F1/F2)
;// (costs 1024+135=1159 bytes)

#define MULTIPLE_CONSOLES


;// SuperCPU support
;// ----------------
;// if you have a CMD SuperCPU you might want to uncomment the following
;// (the system will still run without a SCPU) there is just some code
;// added in order to run well with a SCPU. (otherwise disc accesses
;// will only work, when the SCPU is manually switch to 1MHz).
;// Warning: HAVE_SCPU might conflict with MULTIPLE_CONSOLES
;// (second console $0800-$0fff is not updated by SCPU! - to be confirmed)
;// (costs 39 (+ 512) bytes)

#define HAVE_SCPU


;// Misc stuff
;// ----------
;// always_szu may save some memory (around 265 bytes), but usually
;// slows taskswitching down (up to 160us per taskswitch)

;#define ALWAYS_SZU


;//---------------------------------------------------------------------------
;// end of configurable section

#ifdef HAVE_SCPU
# include <scpu.h>
# define SPEED_MAX    sta SCPU_20MHZ
# define SPEED_1MHZ   sta SCPU_1MHZ
#endif

#ifdef HAVE_REU
# define ALWAYS_SZU
#endif

#ifdef VDC_CONSOLE
# include <vic.h>
# undef MULTIPLE_CONSOLES
# define MULTIPLE_CONSOLES
# define HAVE_VDC
# ifndef HAVE_SCPU
;// C128 without SCPU
#  define SPEED_MAX    lda #1:sta VIC_CLOCK
#  define SPEED_1MHZ   lda #0:sta VIC_CLOCK
# else
#  undef SPEED_MAX
#  undef SPEED_1MHZ	
;// C128 with SCPU (don't know, if this really works)
#  define SPEED_MAX    lda #1:sta VIC_CLOCK:sta SCPU_20MHZ
#  define SPEED_1MHZ   lda #0:sta VIC_CLOCK:sta SCPU_1MHZ
# endif
#endif

#ifndef SPEED_1MHZ	
# define SPEED_MAX
# define SPEED_1MHZ
#endif

#endif