
cimport ctinythreads
# from ctinythreads cimport spawn, yield, lock, unlock


def spawn(fn):
    ctinythreads.spawn(fn)


def yield():
    ctinythreads.yield()


def lock(mutex):
    ctinythreads.lock(mutex)


def unlock(mutex):
    ctinythreads.unloct(mutex)

