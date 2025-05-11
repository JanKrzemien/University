double wyznacznik3x3(double a[3][3])
{
  double c1 = a[0][0]*a[1][1]*a[2][2] + a[0][1]*a[1][2]*a[2][0] + a[0][2]*a[1][0]*a[2][1];
  double c2 = a[0][2]*a[1][1]*a[2][0] + a[0][0]*a[1][2]*a[2][1] + a[0][1]*a[1][0]*a[2][2];
  return c1 - c2;
}

int uklad3(double a[3][3], double b[3], double xyz[3])
{
  double wyznacznikGlowny = wyznacznik3x3(a);

  if(wyznacznikGlowny == 0)
  {
    return 0;
  }

  double ab[3][3];
  
  /* kopiujemy tablice a do ab */
  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++)
      ab[i][j] = a[i][j];
  
  /* dalej podmieniamy kolumny z wartościami z tablicy b i kopiujemy kolumny z tablicy a w miejsce kolumn b z poprzednich wyznaczników */
  for(int i = 0; i < 3; i++)
    ab[i][0] = b[i];

  double wyznacznikX = wyznacznik3x3(ab);

  for(int i = 0; i < 3; i++)
  {
    ab[i][0] = a[i][0];
    ab[i][1] = b[i];
  }

  double wyznacznikY = wyznacznik3x3(ab);

  for(int i = 0; i < 3; i++)
  {
    ab[i][1] = a[i][1];
    ab[i][2] = b[i];
  }

  double wyznacznikZ = wyznacznik3x3(ab);

  xyz[0] = wyznacznikX / wyznacznikGlowny;
  xyz[1] = wyznacznikY / wyznacznikGlowny;
  xyz[2] = wyznacznikZ / wyznacznikGlowny;

  return 1;
}

void sprawdzenie3x3(double a[3][3], double xyz[3], double out[3])
{
  out[0] = a[0][0]*xyz[0] + a[0][1]*xyz[1] + a[0][2]*xyz[2];
  out[1] = a[1][0]*xyz[0] + a[1][1]*xyz[1] + a[1][2]*xyz[2];
  out[2] = a[2][0]*xyz[0] + a[2][1]*xyz[1] + a[2][2]*xyz[2];
}
