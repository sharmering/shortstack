#ifndef __INCprjConfigh
#define __INCprjConfigh

#include "sys/types.h"
#include "archLib.h"

#define RUNTIME_NAME    "Micro eX"
#define RUNTIME_VERSION "1.6"
#define	SYS_MODEL				"Nuvton NUC972"
#define CPU_NAME				"ARM926EJ-S"
#define BOARD_NAME      "PSX6300"
#define HOST_NAME				"PSX6300"
#define UTSNAME_SHORT_NAME		"MEOS"
#define UTSNAME_LONG_NAME		"PSX6300"
#define UTSNAME_OSRELEASE		""
#define UTSNAME_OSVERSION		RUNTIME_VERSION
#define FIRMWARE_NAME			"PSX6300.axf"

#define INCLUDE_REBOOT_HOOKS 1 /* support for hook callouts before reboots */
#define MAX_REBOOT_HOOKS     8

#define SMP_NUM_CPUS	1
#define CPU_INDEX_GET() 0

#define INCLUDE_SW_RANDOM_NUM_GEN 1
#define INCLUDE_RANDOM_DEVICE     1
#define RANDOM_DEVICE_NAME        "/dev/random"
#define URANDOM_DEVICE_NAME       "/dev/urandom"

#define INCLUDE_SEC_HASH_MD5    1
#define INCLUDE_SEC_HASH_RMD    0
#define INCLUDE_SEC_HASH_SHA1   0
#define INCLUDE_SEC_HASH_SHA256 1
#define INCLUDE_SEC_HASH_SHA384 0
#define INCLUDE_SEC_HASH_SHA512 0

/* check stack overflow */
#define INCLUDE_CHECK_STACK_OVERFLOW 1
#define STACK_CHECK_THRESHOLD        16

#define INCLUDE_SEM_BINARY            1 /* binary semaphores */
#define INCLUDE_SEM_MUTEX             1 /* mutex semaphores */
#define INCLUDE_SEM_COUNTING          1 /* counting semaphores */
#define INCLUDE_SEM_READ_WRITE        1
#define SEM_RW_MAX_CONCURRENT_READERS 8
#define INCLUDE_EVENTS                1 /* events */
#define INCLUDE_MSG_Q                 1 /* include message queues */
#define INCLUDE_WATCHDOGS             1 /* include watchdogs */
#define INCLUDE_TLS                   1 /* thread local storage support */
#define INCLUDE_POSIX_PTHREADS        1 /* POSIX pthreads support */
#define INCLUDE_OBJECT_SHOW           1 /* Object show routines */

#define INCLUDE_ISR_DEFER    1 /* Task-level support for ISR deferral */
#define ISR_DEFER_TASK_PRIO  (0)
#define ISR_DEFER_TASK_OPTS  (0)
#define ISR_DEFER_STACK_SIZE (4096)
#define INCLUDE_ENV_VARS  1 /* unix compatable environment variables */
#define ENV_VAR_USE_HOOKS 1

#define INCLUDE_MEM_MGR        1 /* heap memory manager */
#define INCLUDE_MEM_SHOW       1 /* memory manager show */
#define INCLUDE_MEM_PART_CACHE 0 /* memory partition task level memory cache manager */

#define INCLUDE_SYM_TBL        1 /* symbol table package */
#define SYM_TBL_HASH_SIZE_LOG2 8 /* 256 entry hash table symbol table */

#define INCLUDE_ANSI_TIME      1 /* ANSI-C time library functionality */
#define INCLUDE_REALTIME_CLOCK 1 /* realtime clock */

#define INCLUDE_AUX_CLK   1 /* auxiliary clock */
#define INCLUDE_TIMESTAMP 1 /* timestamp driver */
#define TIMESTAMP_HZ      (1000 * 1000)
#define USE_RTC_SYSTICK

#define INCLUDE_IO_SYSTEM      1            /* include I/O system */
#define INCLUDE_IO_REMOVABLE   1            /* I/O device removability (eg USB unplug) */
#define NAME_MAX               FILENAME_MAX /* max filename length excluding EOS */
#define PATH_MAX               FILENAME_MAX /* max pathname length excluding EOS */
#define MAX_DIRNAMES           PATH_MAX
#define MAX_FILENAME_LENGTH    PATH_MAX  /* max chars in filename */
#define NUM_DRIVERS            64        /* max drivers in drvTable */
#define NUM_FILES              512       /* max files open simultaneously */
#define INCLUDE_FORMATTED_IO   1         /* formatted I/O */
#define INCLUDE_FLOATING_POINT 1         /* floating point I/O */
#define INCLUDE_SELECT         1         /* select() facility */
#define FD_SETSIZE             NUM_FILES /* Select uses bit masks of file descriptors in longs */

#define INCLUDE_VRFS 1 /* virtual root file system */
#define INCLUDE_EPOLL          1         /* Event poll facility */

#define INCLUDE_DOSFS                1  /* dosFs FAT12/16/32 FAT table handler */
#define DOSFS_DEFAULT_MAX_FILES      64 /* max dosFs files open */
#define DOSFS_DEFAULT_CREATE_OPTIONS (DOS_CHK_REPAIR | DOS_CHK_VERB_0)
#define INCLUDE_DOSFS_FMT            1 /* dosFs2 file system formatting module */
#define INCLUDE_DOSFS_CHKDSK         1 /* file system integrity checking */
#define SIZE64

#define INCLUDE_SERIAL    ((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10))
#define CONSOLE_BAUD_RATE 115200
#define CONSOLE_TTY       0
#define INCLUDE_TTY_DEV   INCLUDE_SERIAL /* attach serial drivers */
#define TYCO_BUFSZ        2048
#define INCLUDE_TYLIB          1  /* serial driver support lib */
#define TYLIB_XOFF_PCNT        85 /* XOFF at 85% full */
#define TYLIB_XON_PCNT         50 /* XON at 50% full */
#define TYLIB_WRT_THRESHLD     20 /* wakeup at 20 chars in tx buff */
#define TYLIB_MON_TRAP_DISABLE FALSE

#define INCLUDE_KWRITE_SIO 1
#define KWRITE_TTY         0
#define KWRITE_BAUD_RATE   115200

#define INCLUDE_SHELL        1 /* Include interactive interpreter */
#define MAX_PROMPT_LEN       40
#define MAX_SHELL_LINE        512         /* max chars on line typed to shell */
#define SHELL_TASK_PRIORITY  16          /* shell Task priority */
#define SHELL_TASK_STACK_SIZE (32 * 1024) /* shell Task Stack size */
#define SHELL_PROMPT_DFLT    "$P$G"
#define SHELL_HISTORY_SIZE   4096 /* History buffer size */
#define INCLUDE_SHELL_BANNER 1    /* version information */

#define MAX_SPY_TASKS 32 /* max tasks that can be spy'd */

#define XMODEM_OPT_DFLT XMODEM_OPT_1K /* XMODEM default options */

#define INCLUDE_ERF            1 /* Event reporting framework */
#define ERF_QUEUE_SIZE         16
#define ERF_MAX_USR_CATEGORIES 32
#define ERF_MAX_USR_TYPES      32
#define ERF_TASK_STACK_SIZE         8192
#define ERF_TASK_PRIORITY      10
#define ERF_TASK_OPTIONS		0

#define INCLUDE_DEVICE_MANAGER         1 /* Device manager */
#define DEVICE_MANAGER_MAX_NUM_DEVICES 32

#define INCLUDE_CBIO         1    /* CBIO API module */
#define INCLUDE_DISK_CACHE   1    /* CBIO API disk caching layer */
#define DCACHE_STACK_SIZE    4096 /* dcacheUpdTask stack size */
#define DCACHE_TASK_PRIORITY 60   /* dcacheUpdTask priority */

#define INCLUDE_XBD 1 /* Extended block device */

#define INCLUDE_FS_EVENT_UTIL 1 /* File system event utility */
#define INCLUDE_FS_MONITOR    1 /* File system monitor */

#define INCLUDE_RAWFS       1 /* rawFs file system */
#define RAWFS_DEF_MAX_FILES 8 /* default max number of open files */

#define INCLUDE_LOGGING   1 /* logTask logging facility */
#define LOG_TASK_PRIORITY 63
#define LOG_TASK_STACK_SIZE    8192
#define LOG_TASK_OPTIONS 	0
#define MAX_LOG_FDS       8
#define MAX_LOG_MSG_QUEUE	64
#define MAX_LOG_POOL_SIZE	(16 * 1024)
#define LOG_FD_DEFAULT      consoleFd
#define INCLUDE_SYSLOG		0

/* TrueFFS support */
#define INCLUDE_TFFS   1
#define MAX_NAND_FLASH 1
#define MALLOC_TFFS(size) KMEM_ALLOC((size))
#define FREE_TFFS(pBuf)   KMEM_FREE((pBuf))
#define NFTL_CACHE
#define EXTRA_LARGE
#define EXTRA_UNIT_SIZE
#define TFFS_MAX_DRIVES       1 /* maximum number of drives (and sockets) supported */
#define TFFS_POLLING_INTERVAL 0 /* Polling interval in millisec */
#define TFFS_STACK_SIZE       0 /* Polling task stack size */
#define TFFS_TASK_PRIORITY    PRIORITY_LOWEST
#define TFFS_VERIFY_WRITE     FL_UPS
#define TFFS_VERIFY_ERASED_SECTOR
#define SECTORS_VERIFIED_PER_FOLDING 64
#define TFFS_BACKGROUND_TASK         1
#define TFFS_SVC_TASK_PRIO           50
#define TFFS_SVC_TASK_OPTIONS        0
#define TFFS_SVC_TASK_STACK_SIZE     2048

#define NDM9000           4
#define NET_TASK_PRIORITY 16   /* network task Priority */
#define NET_TASK_OPTIONS    0
#define NET_TASK_STACK_SIZE    8192 /* network task stack size */
#define NET_JOB_QUEUE_SIZE  64   /* Max # of netowrk jobs */
#define ARP_MAX_ENTRIES   128
#define USR_MAX_LINK_HDR  16
#define MAX_LINK_NOTIFY_RTNS	4
#define MII_MONITOR_TASK_OPTIONS	0
#define MII_MONITOR_TASK_STACK_SIZE	(8 * 1024)

#define INCLUDE_BSD_SOCKET    1
#define INCLUDE_ROUTE_SOCK    1
#define INCLUDE_MCAST_ROUTING 0
#define INCLUDE_LOOPBACK      1
#define INCLUDE_IGMP          1
#define INCLUDE_ICMP          1
#define INCLUDE_TCP           1
#define INCLUDE_IP_FILTER     0
#define INCLUDE_UDP           1
#define INCLUDE_ARP_API       1
#define INCLUDE_DNS_DEBUG     0 /* DNS resolver debug mode */
#define INCLUDE_DNS_RESOLVER  1 /* DNS resolver */
#define INCLUDE_NET_SHOW      1
#define INCLUDE_ICMP_SHOW     1
#define INCLUDE_IGMP_SHOW     1
#define INCLUDE_TCP_SHOW      1
#define INCLUDE_UDP_SHOW      1
#define INCLUDE_DHCPC_SHOW    1

#define INCLUDE_DHCPC             1               /* DHCP client */
#define DHCPC_STATE_TASK_PRIORITY PRIORITY_NORMAL /* Priority level of DHCP state task */
#define DHCPC_STATE_STACK_SIZE    8192            /* Stack size for DHCP state task */
#define DHCPC_READ_TASK_PRIORITY  PRIORITY_NORMAL /* Priority level of DHCP read task */
#define DHCPC_READ_STACK_SIZE     8192            /* Stack size for DHCP read task */
#define DHCPC_SPORT               67              /* Port monitored by DHCP servers. */
#define DHCPC_CPORT               68              /* Port monitored by DHCP clients. */
#define DHCPC_MAX_SLOT            10
#define DHCPC_MAX_LEASES          10   /* Max. number of simultaneous leases */
#define DHCPC_OFFER_TIMEOUT       5    /* Seconds to wait for multiple offers */
#define DHCPC_DEFAULT_LEASE       3600 /* Desired lease length in seconds */
#define DHCPC_MIN_LEASE           30   /* Minimum allowable lease length */
#define DHCPC_MAX_MSGSIZE         590  /* Allows minimum message on Ethernet */

#define INCLUDE_DHCPS       1               /* DHCP server */
#define INCLUDE_DHCPR       0               /* DHCP relay agent */
#define DHCPS_TASK_PRIORITY PRIORITY_NORMAL /* Priority level of DHCP server */
#define DHCPS_STACK_SIZE    8192            /* Stack size for DHCP server task */
#define DHCPS_LEASE_HOOK    NULL            /* Name of required storage routine */
#define DHCPS_ADDRESS_HOOK  NULL            /* Name of optional storage routine */
#define DHCPS_DEFAULT_LEASE 3600            /* default lease length (secs). */
#define DHCPS_MAX_LEASE     3600            /* default value of max lease (secs). */
#define DHCP_MAX_HOPS       4               /* Hops before discard, up to 16. */
#define DHCPS_SPORT         67              /* Port monitored by DHCP servers */
#define DHCPS_CPORT         68              /* Port monitored by DHCP clients */
#define DHCPS_MAX_MSGSIZE   590             /* Allows minimum message on Ethernet */

#define INCLUDE_TELNETD     1
#define TELNETD_STACK_SIZE  8192
#define TELNETD_PRIORITY    PRIORITY_NORMAL
#define TELNETD_MAX_CLIENTS 1

#define INCLUDE_FTP_SERVER 1 /* ftp server */
#define FTPD_WINDOW_SIZE   4096
#define FTPD_ROOT_DFLT     "/"
#define FTP_DATA_PORT      20
#define FTP_DAEMON_PORT    21
#define FTPD_TASK_STACK_SIZE	(8 * 1024)

#define INCLUDE_SNTPS       1
#define SNTPS_TASK_PRIORITY 32
#define SNTPS_STACK_SIZE    4000
#define SNTPS_PORT          123

#define INCLUDE_TFTPD       1 /* tftp server */
#define TFTPD_TASK_PRIORITY PRIORITY_NORMAL
#define TFTPD_STACK_SIZE    4096

#define INCLUDE_RLOGIN     1 /* remote login */
#define RLOG_TASK_PRIORITY PRIORITY_NORMAL
#define RLOG_STACK_SIZE    4096

#define INCLUDE_SECURITY  1
#define LOGIN_USER_NAME   "admin"
#define LOGIN_PASSWORD    "bydezeydQQ" /* admin123 */
#define LOGIN_ENCRYPT_RTN NONE

#define ROOT_TASK_STACK_SIZE (64 * 1024) /* root Task Stack size */
#define IDLE_TASK_STACK_SIZE (8 * 1024)  /* idle Task Stack size */
#define INCLUDE_EXC_TASK   1
#define MAX_ISR_JOBS       64
#define ISR_JOB_MAX_ARGS   3
#define EXC_TASK_PRIORITY  0 /* excTask always at the highest priority */
#define EXC_TASK_STACKSIZE (8 * 1024)
#define EXC_TASK_OPTIONS   0

#define MAX_KERN_JOBS  64
#define ROUNDROBIN_SLICE     5 /* round robin task slice in ticks */
#define MAX_TASK_COOKIES     1 /* num of cookie variable in tcb */
#define MAX_TASK_ARGS        4 /* max args passed to a task */
#define INCLUDE_TASK_VARS    1 /* task variable package */
#define MAX_TASK_CREATE_RTNS 4 /* max task create callout routines */
#define MAX_TASK_DELETE_RTNS 4 /* max task delete callout routines */
#define MAX_IDLE_ENTER_RTNS	4	/* max idle enter callout routines */
#define INCLUDE_CPU_METRICS  1 /* CPU load metrics */
#define INCLUDE_TASK_SHOW    1 /* tasks statistics */

#define INCLUDE_TICKLESS_IDLE	0			/* Tickless idle component */
#define CPU_SLEEP_MODE_LONG_THRESHOLD	1

#define INCLUDE_FDT_DEVICE     1                     /* FDT bus library */

/* DMA supported */
#define INCLUDE_DMA      1
#define INCLUDE_DMA_SHOW 1
#define NUM_DMA_CHANS    2

#define FLASH_DISK  "/fd"
#define SDCARD_DISK "/sd"

/* cache support */
#define INCLUDE_CACHE_SUPPORT 1

#if INCLUDE_CACHE_SUPPORT
#define USER_I_CACHE_MODE CACHE_COPYBACK
#define USER_D_CACHE_MODE CACHE_COPYBACK
#define USER_B_CACHE_MODE CACHE_DISABLED
#define _CACHE_ALIGN_SIZE   (cacheArchAlignSize)
#ifdef HEAP_DEBUG
#define CACHE_DMA_MALLOC(nBytes) cacheDmaMallocDbg(nBytes, __FILE__, __LINE__)
#else /* HEAP_DEBUG */
#define CACHE_DMA_MALLOC(nBytes) cacheDmaMalloc(nBytes)
#endif
#define CACHE_DMA_FREE(pChar) cacheDmaFree(pChar)
#else
#define USER_I_CACHE_MODE      CACHE_DISABLE
#define USER_D_CACHE_MODE      CACHE_DISABLE
#define USER_B_CACHE_MODE      CACHE_DISABLE
#define _CACHE_ALIGN_SIZE        _ALLOC_ALIGN_SIZE
#define CACHE_DMA_MALLOC(nBytes) KMEM_ALLOC(nBytes)
#define CACHE_DMA_FREE(pChar)    KMEM_FREE(pChar)
#endif /* INCLUDE_CACHE_SUPPORT */

/* default system clock rate */
#define __CLK_TCK    128
#define SYS_CLK_RATE __CLK_TCK /* default system clock rate */
#define CPU          NUC970

#define RAM_BASE_ADRS 0x30000000  /* RAM base address */
#define RAM_SIZE      (56 * 1024) /* RAM size */

#define FIN 12000000


#endif /* __INCprjConfigh */
