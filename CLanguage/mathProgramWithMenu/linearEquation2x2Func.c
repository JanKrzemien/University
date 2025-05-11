/* bez * gwiazdki bo to by była tablica wskaźników, i musimy podać rozmiar tablicy, jeśli tablica kwadratowa to możemy podać wymiar tylko w drugim nawiasie */
double wyznacznik(double a[2][2])
{
  return (a[0][0]*a[1][1] - a[0][1]*a[1][0]);
}

int uklad2(double a[][2], double b[2], double xy[2])
{
  double wyznacznikGlowny = wyznacznik(a);

  /* zapis bardziej skrócony {{b[0], a[0][1]}, {b[1], a[1][1]}} */
  double ab[2][2];
  ab[0][0] = b[0];
  ab[0][1] = a[0][1];
  ab[1][0] = b[1];
  ab[1][1] = a[1][1];
  double wyznacznikX = wyznacznik(ab);

  /* zapis bardziej skrócony {{a[0][0], b[0]}, {a[1][0], b[1]}} */
  ab[0][0] = a[0][0];
  ab[0][1] = b[0];
  ab[1][0] = a[1][0];
  ab[1][1] = b[1];
  double wyznacznikY = wyznacznik(ab);

  if(wyznacznikGlowny != 0)
  {
    xy[0] = wyznacznikX/wyznacznikGlowny;
    xy[1] = wyznacznikY/wyznacznikGlowny;

    return 1;
  }
  /* 1000 jest umowne i oznacza nieskończnie wiele rozwiązań */
  if(wyznacznikY == 0 && wyznacznikX == 0)
    return 1000;

  return 0;
}

void sprawdzenie(double a[2][2], double xy[2], double out[2])
{
  out[0] = a[0][0]*xy[0] + a[0][1]*xy[1];
  out[1] = a[1][0]*xy[0] + a[1][1]*xy[1];
  return;
}
