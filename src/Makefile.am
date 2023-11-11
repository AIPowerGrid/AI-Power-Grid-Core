# Copyright (c) 2013-2016 The Bitcoin Core developers
# Copyright (c) 2017-2019 The AIPG Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS) $(ERROR_CXXFLAGS)
AM_CPPFLAGS = $(HARDENED_CPPFLAGS)
EXTRA_LIBRARIES =

if EMBEDDED_UNIVALUE
LIBUNIVALUE = univalue/libunivalue.la

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
else
LIBUNIVALUE = $(UNIVALUE_LIBS)
endif

AIPG_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

AIPG_INCLUDES += -I$(srcdir)/secp256k1/include
AIPG_INCLUDES += $(UNIVALUE_CFLAGS)

LIBAIPG_SERVER=libaipg_server.a
LIBAIPG_COMMON=libaipg_common.a
LIBAIPG_CONSENSUS=libaipg_consensus.a
LIBAIPG_CLI=libaipg_cli.a
LIBAIPG_UTIL=libaipg_util.a
LIBAIPG_CRYPTO=crypto/libaipg_crypto.a
LIBAIPGQT=qt/libaipgqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

if ENABLE_ZMQ
LIBAIPG_ZMQ=libaipg_zmq.a
endif
if BUILD_AIPG_LIBS
LIBAIPGCONSENSUS=libaipgconsensus.la
endif
if ENABLE_WALLET
LIBAIPG_WALLET=libaipg_wallet.a
endif

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBAIPG_CRYPTO) \
  $(LIBAIPG_UTIL) \
  $(LIBAIPG_COMMON) \
  $(LIBAIPG_CONSENSUS) \
  $(LIBAIPG_SERVER) \
  $(LIBAIPG_CLI) \
  $(LIBAIPG_WALLET) \
  $(LIBAIPG_ZMQ)

lib_LTLIBRARIES = $(LIBAIPGCONSENSUS)

bin_PROGRAMS =
noinst_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_AIPGD
  bin_PROGRAMS += aipgd
endif

if BUILD_AIPG_CLI
  bin_PROGRAMS += aipg-cli
endif

if BUILD_AIPG_TX
  bin_PROGRAMS += aipg-tx
endif

.PHONY: FORCE check-symbols check-security
# aipg core #
AIPG_CORE_H = \
  addrdb.h \
  addressindex.h \
  algo/sph_groestl.h \
  algo/sph_types.h \
  algo/sph_blake.h \
  algo/sph_bmw.h \
  algo/sph_jh.h \
  algo/sph_keccak.h \
  algo/sph_skein.h \
  algo/sph_luffa.h \
  algo/sph_cubehash.h \
  algo/sph_simd.h \
  algo/sph_echo.h \
  algo/sph_shavite.h \
  algo/sph_sha2.h \
  algo/sph_haval.h \
  algo/sph_tiger.h \
  algo/lyra2.h \
  algo/sponge.h \
  algo/gost_streebog.h \
  algo/groestl.c \
  algo/blake.c \
  algo/bmw.c \
  algo/cubehash.c \
  algo/echo.c \
  algo/jh.c \
  algo/keccak.c \
  algo/luffa.c \
  algo/shavite.c \
  algo/simd.c \
  algo/skein.c \
  algo/hamsi.c \
  algo/whirlpool.c \
  algo/shabal.c \
  algo/fugue.c \
  algo/sha2.c \
  algo/extra.c \
  algo/extra.h \
  algo/sph_sha2big.c \
  algo/haval.c \
  algo/tiger.cpp \
  algo/lyra2.cpp \
  algo/sponge.cpp \
  algo/sph_sha2.c \
  algo/gost_streebog.c \
  spentindex.h \
  timestampindex.h \
  addrman.h \
  assets/assets.h \
  assets/assetdb.h \
  assets/assettypes.h \
  assets/messages.h \
  assets/myassetsdb.h \
  assets/restricteddb.h \
  assets/snapshotrequestdb.h \
  assets/assetsnapshotdb.h \
  assets/rewards.h \
  base58.h \
  bloom.h \
  blockencodings.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  consensus/tx_verify.h \
  core_io.h \
  core_memusage.h \
  cuckoocache.h \
  fs.h \
  httprpc.h \
  httpserver.h \
  indirectmap.h \
  init.h \
  key.h \
  keystore.h \
  dbwrapper.h \
  limitedmap.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  net.h \
  net_processing.h \
  netaddress.h \
  netbase.h \
  netmessagemaker.h \
  noui.h \
  policy/feerate.h \
  policy/fees.h \
  policy/policy.h \
  policy/rbf.h \
  pow.h \
  protocol.h \
  random.h \
  reverse_iterator.h \
  reverselock.h \
  rpc/blockchain.h \
  rpc/client.h \
  rpc/mining.h \
  rpc/protocol.h \
  rpc/safemode.h \
  rpc/server.h \
  rpc/register.h \
  scheduler.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  script/ismine.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/events.h \
  support/lockedpool.h \
  sync.h \
  threadsafety.h \
  threadinterrupt.h \
  timedata.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utiltime.h \
  validation.h \
  validationinterface.h \
  versionbits.h \
  wallet/coincontrol.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/feebumper.h \
  wallet/fees.h \
  wallet/init.h \
  wallet/rpcwallet.h \
  wallet/wallet.h \
  wallet/walletdb.h \
  wallet/bip39.h \
  wallet/bip39_english.h \
  warnings.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h\
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh "$(abs_top_builddir)/src/obj/build.h" \
	  "$(abs_top_srcdir)"
libaipg_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between aipgd and aipg-qt
libaipg_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(AIPG_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libaipg_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libaipg_server_a_SOURCES = \
  addrdb.cpp \
  addrman.cpp \
  bloom.cpp \
  blockencodings.cpp \
  chain.cpp \
  checkpoints.cpp \
  consensus/consensus.cpp \
  consensus/tx_verify.cpp \
  httprpc.cpp \
  httpserver.cpp \
  init.cpp \
  dbwrapper.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  net_processing.cpp \
  noui.cpp \
  assets/assets.cpp \
  assets/assetdb.cpp \
  assets/assettypes.cpp \
  assets/messages.cpp \
  assets/myassetsdb.cpp \
  assets/restricteddb.cpp \
  assets/snapshotrequestdb.cpp \
  assets/assetsnapshotdb.cpp \
  assets/rewards.cpp \
  policy/fees.cpp \
  policy/policy.cpp \
  policy/rbf.cpp \
  pow.cpp \
  rest.cpp \
  rpc/assets.cpp \
  rpc/blockchain.cpp \
  rpc/messages.cpp \
  rpc/mining.cpp \
  rpc/misc.cpp \
  rpc/net.cpp \
  rpc/rawtransaction.cpp \
  rpc/rewards.cpp \
  rpc/safemode.cpp \
  rpc/server.cpp \
  script/sigcache.cpp \
  script/ismine.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  ui_interface.cpp \
  validation.cpp \
  validationinterface.cpp \
  versionbits.cpp \
  $(AIPG_CORE_H)

if ENABLE_ZMQ
libaipg_zmq_a_CPPFLAGS = $(AIPG_INCLUDES) $(ZMQ_CFLAGS)
libaipg_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libaipg_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp
endif


# wallet: shared between aipgd and aipg-qt, but only linked
# when wallet enabled
libaipg_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(AIPG_INCLUDES)
libaipg_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libaipg_wallet_a_SOURCES = \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/feebumper.cpp \
  wallet/fees.cpp \
  wallet/init.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  wallet/bip39.cpp \
  $(AIPG_CORE_H)

# crypto primitives library
crypto_libaipg_crypto_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libaipg_crypto_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libaipg_crypto_a_SOURCES = \
  crypto/aes.cpp \
  crypto/aes.h \
  crypto/chacha20.h \
  crypto/chacha20.cpp \
  crypto/common.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/ripemd160.cpp \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.h \
  crypto/sha512.cpp \
  crypto/ethash/include/ethash/ethash.h \
  crypto/ethash/include/ethash/ethash.hpp \
  crypto/ethash/include/ethash/hash_types.h \
  crypto/ethash/include/ethash/hash_types.hpp \
  crypto/ethash/include/ethash/keccak.h \
  crypto/ethash/include/ethash/keccak.hpp \
  crypto/ethash/include/ethash/progpow.hpp \
  crypto/ethash/include/ethash/version.h \
  crypto/ethash/lib/ethash/bit_manipulation.h \
  crypto/ethash/lib/ethash/builtins.h \
  crypto/ethash/lib/ethash/endianness.hpp \
  crypto/ethash/lib/ethash/ethash.cpp \
  crypto/ethash/lib/ethash/ethash-internal.hpp \
  crypto/ethash/lib/ethash/kiss99.hpp \
  crypto/ethash/lib/ethash/managed.cpp \
  crypto/ethash/lib/ethash/primes.c \
  crypto/ethash/lib/ethash/primes.h \
  crypto/ethash/lib/ethash/progpow.cpp \
  crypto/ethash/lib/keccak/keccak.c \
  crypto/ethash/lib/keccak/keccakf1600.c \
  crypto/ethash/lib/keccak/keccakf800.c \
  crypto/ethash/lib/support/attributes.h \
  crypto/ethash/helpers.hpp \
  crypto/ethash/progpow_test_vectors.hpp

if USE_ASM
crypto_libaipg_crypto_a_SOURCES += crypto/sha256_sse4.cpp
endif

# consensus: shared between all executables that validate any consensus rules.
libaipg_consensus_a_CPPFLAGS = $(AM_CPPFLAGS) $(AIPG_INCLUDES)
libaipg_consensus_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libaipg_consensus_a_SOURCES = \
  amount.h \
  arith_uint256.cpp \
  arith_uint256.h \
  consensus/merkle.cpp \
  consensus/merkle.h \
  consensus/params.h \
  consensus/validation.h \
  hash.cpp \
  hash.h \
  prevector.h \
  primitives/block.cpp \
  primitives/block.h \
  primitives/transaction.cpp \
  primitives/transaction.h \
  pubkey.cpp \
  pubkey.h \
  script/aipgconsensus.cpp \
  script/interpreter.cpp \
  script/interpreter.h \
  script/script.cpp \
  script/script.h \
  script/script_error.cpp \
  script/script_error.h \
  serialize.h \
  support/cleanse.h \
  support/cleanse.cpp \
  tinyformat.h \
  uint256.cpp \
  uint256.h \
  utilstrencodings.cpp \
  utilstrencodings.h \
  version.h \
  LibBoolEE.cpp \
  LibBoolEE.h \
  $(AIPG_CORE_H)

# common: shared between aipgd, and aipg-qt and non-server tools
libaipg_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(AIPG_INCLUDES)
libaipg_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libaipg_common_a_SOURCES = \
  base58.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  key.cpp \
  keystore.cpp \
  netaddress.cpp \
  netbase.cpp \
  policy/feerate.cpp \
  protocol.cpp \
  scheduler.cpp \
  script/sign.cpp \
  script/standard.cpp \
  warnings.cpp \
  $(AIPG_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libaipg_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(AIPG_INCLUDES)
libaipg_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libaipg_util_a_SOURCES = \
  support/lockedpool.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  fs.cpp \
  random.cpp \
  rpc/protocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  threadinterrupt.cpp \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(AIPG_CORE_H)

if GLIBC_BACK_COMPAT
libaipg_util_a_SOURCES += compat/glibc_compat.cpp
AM_LDFLAGS += $(COMPAT_LDFLAGS)
endif

# cli: shared between aipg-cli and aipg-qt
libaipg_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(AIPG_INCLUDES)
libaipg_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libaipg_cli_a_SOURCES = \
  rpc/client.cpp \
  $(AIPG_CORE_H)

nodist_libaipg_util_a_SOURCES = $(srcdir)/obj/build.h
#

# aipgd binary #
aipgd_SOURCES = aipgd.cpp
aipgd_CPPFLAGS = $(AM_CPPFLAGS) $(AIPG_INCLUDES)
aipgd_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
aipgd_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
aipgd_SOURCES += aipgd-res.rc
endif

aipgd_LDADD = \
  $(LIBAIPG_SERVER) \
  $(LIBAIPG_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBAIPG_UTIL) \
  $(LIBAIPG_WALLET) \
  $(LIBAIPG_ZMQ) \
  $(LIBAIPG_CONSENSUS) \
  $(LIBAIPG_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBLEVELDB_SSE42) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

aipgd_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS)

# aipg-cli binary #
aipg_cli_SOURCES = aipg-cli.cpp
aipg_cli_CPPFLAGS = $(AM_CPPFLAGS) $(AIPG_INCLUDES) $(EVENT_CFLAGS)
aipg_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
aipg_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
aipg_cli_SOURCES += aipg-cli-res.rc
endif

aipg_cli_LDADD = \
  $(LIBAIPG_CLI) \
  $(LIBUNIVALUE) \
  $(LIBAIPG_UTIL) \
  $(LIBAIPG_CRYPTO)

aipg_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS)
#

# aipg-tx binary #
aipg_tx_SOURCES = aipg-tx.cpp
aipg_tx_CPPFLAGS = $(AM_CPPFLAGS) $(AIPG_INCLUDES)
aipg_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
aipg_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
aipg_tx_SOURCES += aipg-tx-res.rc
endif

aipg_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBAIPG_COMMON) \
  $(LIBAIPG_UTIL) \
  $(LIBAIPG_CONSENSUS) \
  $(LIBAIPG_CRYPTO) \
  $(LIBSECP256K1)

aipg_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# aipgconsensus library #
if BUILD_AIPG_LIBS
include_HEADERS = script/aipgconsensus.h
libaipgconsensus_la_SOURCES = $(crypto_libaipg_crypto_a_SOURCES) $(libaipg_consensus_a_SOURCES)

if GLIBC_BACK_COMPAT
  libaipgconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libaipgconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libaipgconsensus_la_LIBADD = $(LIBSECP256K1) $(BOOST_LIBS)
libaipgconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_AIPG_INTERNAL
libaipgconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

CLEANFILES = $(EXTRA_LIBRARIES)

CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno
CLEANFILES += obj/build.h

EXTRA_DIST = $(CTAES_DIST)


config/aipg-config.h: config/stamp-h1
	@$(MAKE) -C $(top_builddir) $(subdir)/$(@)
config/stamp-h1: $(top_srcdir)/$(subdir)/config/aipg-config.h.in $(top_builddir)/config.status
	$(AM_V_at)$(MAKE) -C $(top_builddir) $(subdir)/$(@)
$(top_srcdir)/$(subdir)/config/aipg-config.h.in:  $(am__configure_deps)
	$(AM_V_at)$(MAKE) -C $(top_srcdir) $(subdir)/config/aipg-config.h.in

clean-local:
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h
	-rm -rf test/__pycache__

.rc.o:
	@test -f $(WINDRES)
	## FIXME: How to get the appropriate modulename_CPPFLAGS in here?
	$(AM_V_GEN) $(WINDRES) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) -DWINDRES_PREPROC -i $< -o $@

check-symbols: $(bin_PROGRAMS)
if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat..."
	$(AM_V_at) READELF=$(READELF) CPPFILT=$(CPPFILT) $(top_srcdir)/contrib/devtools/symbol-check.py < $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(top_srcdir)/contrib/devtools/security-check.py < $(bin_PROGRAMS)
endif

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(<D) $<

if EMBEDDED_LEVELDB
include Makefile.leveldb.include
endif

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
