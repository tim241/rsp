/* DLL configurator control head by Iconoclast
 *
 * Macro controls over RSP virtualization behaviors are all switched here.
 * There is no GUI to config such as zilmar's `DllConfig` export because
 * obviously such run-time checks slow down the emulation by checking the
 * configurations per billions of opcode iterations.  Anyone can add a WINGUI
 * config if they like, but I doubt that the performance impact is worth it.
 */

#define _CRT_SECURE_NO_WARNINGS
/* This is only here for people using modern Microsoft compilers.
 * Usually the default warning level complains over "deprecated" CRT methods.
 * It's basically Microsoft's way of saying they're better than everyone.
 */

#undef  MINIMUM_MESSAGE_PRIORITY
/* Many people will have different uses for an RSP emulator.
 * Some people only want to see message boxes for definite RSP LLE errors.
 * Other people are interested in being notified of technical RSP oddities.
 * I have standardized the following priority levels for message boxes:
 *     0:  Any and all message interrupts in this code will notify the user.
 *     1:  Interrupt SP emulation with messages of at least curious cases.
 *     2:  Draw message boxes for N64 situations *probably* unemulated.
 *     3:  Only notify the user of absolute problems in the emulator.
 *     4:  Disable all message printing (less CRT/USER32 lib dependency)
 *         (and also less interference with leisure of full-screen game play)
 * This macro is mainly for maintainability as well as cross-OS portability
 * by calling a custom method which uses the API-specific message print call.
 * See the `void message()` for details on this centralized API invocation.
 */

#undef  MAX_WAIT
/* How many times did the new PC match the previous PC?  If that exceeds
 * `MAX_WAIT`, we assume that the loop is infinite.  We try to exit two types
 * of loops:  simple and complex.  See `SEARCH_INFINITE_LOOPS` for details.
 */

#undef  EXTERN_COMMAND_LIST_GBI
/* If this is defined, the RSP never executes graphics tasks.
 * Those will all be sent to the video plugin for simulation processing.
 */
#undef  EXTERN_COMMAND_LIST_ABI
/* If this is defined, the RSP never executes audio tasks; use audio plugin.
 * Enabling both of these does not guarantee that the RSP will never execute.
 */

#undef  SEMAPHORE_LOCK_CORRECTIONS
/* The CPU-RSP semaphore is a lock defining synchronization with the host.
 * As of the time in which bpoint reversed the RSP, host interpretation of
 * this lock was incorrect.  The problem has been inherent for a very long
 * time until a rather recent update applied between Project64 1.7:2.0.
 *
 * If this is on, 1964 and Mupen64 will have no sound for [any?] games.
 * It will be almost completely useless on Project64 1.6 or older.
 * The exception is HLE audio, where it will work for almost every game.
 *
 * Keep this off when using audio LLE or playing games booting off the NUS-
 * CIC-6105 chip (also uses the semaphore); keep it on with Project64 2.0.
 */

#undef  SEARCH_INFINITE_LOOPS
/* The most common use for this is to compensate for cycle-accuracy misses by
 * the master processor (the MIPS R4300 CPU), which go hand-in-hand with this
 * processor (the slave, the RSP, under the RCP) in managing the SP_STATUS
 * register's signal flags (SP_STATUS_SIG7..SP_STATUS_SIG0), used for vendor-
 * defined synchronization between the master and the RSP slave.  As today's
 * emulators conforming to zilmar's limited plugin specifications have issues
 * managing RSP cycle timing, the presence of this hack in a zilmar-spec RSP
 * emulator is somewhat mandatory for success, although it is inaccurate.
 *
 * Whatever the cause of the permanent loop, as assumed by the MAX_WAIT test,
 * the RSP CPU will eventually enter a search loop back-tracking to the most
 * recent branch instruction that was missed and unconditionally take that
 * branch in an attempt to recover from the loop.  (The exact behavior of the
 * search based on what type of jump/branch order is beyond this scope.)
 */

#undef  SP_EXECUTE_LOG
/* This is my mechanism to use file output of 32 bits per each SP operation.
 * I use this in conjunction with my EXE to handle debug, but still checking
 * every single frame even with file output turned off is ~1-2 VI/s slower.
 */

#undef  VU_EMULATE_SCALAR_ACCUMULATOR_READ
/* VSAW is the only RSP instruction that can access the vector accumulator
 * elements directly.  In the original RSP for Ultra64 this was supposed to
 * be called `VSAR` "Vector Accumulator Read (and Write)".  (The 'S' probably
 * means "Scalar", if not "Select" or "Store".)  Current RSP emulators agree
 * that in VSAW, the accumulator is copied over to VR[vd], but there is a new
 * step no emulator supports.  In the original VSAR, that behavior is before
 * VR[vs] is copied to those accumulator elements.  By the time this opcode
 * got renamed to "VSAW", however, the acknowledgement of this ceased to be.
 */

/* Choose whether to define, or keep undefined, the above macros. */
#define MINIMUM_MESSAGE_PRIORITY    1 // show most messages of RSP weirdness
#define MAX_WAIT                    (0x0001FFFF & 0x1FFFFFFF)
// #define EXTERN_COMMAND_LIST_GBI // Not really recommended but user preference
// #define EXTERN_COMMAND_LIST_ABI // Not really significant but user preference
// #define SEMAPHORE_LOCK_CORRECTIONS // Recommended only for CPUs supporting it
// #define SEARCH_INFINITE_LOOPS // Try with Gauntlet Legends, Stunt Racer 64...
// #define SP_EXECUTE_LOG // For debugging only.  Keep it off to free CPU.
// #define VU_EMULATE_SCALAR_ACCUMULATOR_READ // experimental but needs tests

#if defined EXTERN_COMMAND_LIST_GBI && defined EXTERN_COMMAND_LIST_ABI
#define L_TITLE "Basic RSP Simulator"
#elif defined EXTERN_COMMAND_LIST_GBI || defined EXTERN_COMMAND_LIST_ABI
#define L_TITLE "Iconoclast's MLE Test"
#else
#define L_TITLE "RSP Interpreter"
#endif
#define L_ABOUT "Thanks for test RDP:  Jabo, ziggy, Gonetz\n"\
                "SP thread examples:  bpoint, zilmar, Ville Linde"
