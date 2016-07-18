# Maintainer: Peter Mount <peter@retep.org>

pkgname="libarea51"
pkgver="0.1"
pkgrel="3"
pkgdesc="Area51 core C library"
arch="x86_64"
url="https://area51.onl/"
license="ASL 2.0"
source=""
subpackages="$pkgname-dev $pkgname-json $pkgname-jsondev"
depends="curl"
depends_dev="curl-dev"
#triggers="$pkgname-bin.trigger=/lib:/usr/lib:/usr/glibc-compat/lib"

builddeps() {
  sudo apk add $depends $depends_dev
}

package() {
  autoconf
  ./configure
  make clean
  make
  mkdir -p "$pkgdir/usr/lib"
  cp -rp build/package/usr/lib/* "$pkgdir/usr/lib"
}

dev() {
  depends="$pkgname libarea51"
  mkdir -p "$subpkgdir/usr/include"
  cp -rp build/package/usr/include/* "$subpkgdir/usr/include"
  rm "$subpkgdir/usr/include/area51/json.h"
}

json() {
  depends="libarea51 json-c"
  mkdir -p "$subpkgdir/usr/include"
  cp -rp build/package/usr/include/* "$subpkgdir/usr/include"
}

jsondev() {
  depends="libarea51-json libarea51 json-c-dev"
  mkdir -p "$subpkgdir/usr/include/area51"
  cp -rp build/package/usr/include/area51/json.h "$subpkgdir/usr/include/area51"
}
