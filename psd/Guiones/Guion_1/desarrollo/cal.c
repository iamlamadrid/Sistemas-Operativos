
float calculo(numero, x, y, pendiente, abcisa, ordenada)

    int numero;
    float x[], y[];
    float *pendiente, *abcisa, *ordenada;

{

   float sumax=0.0, sumay=0.0, sumax2=0.0, sumay2=0.0, sumaxy=0.0;
   float mediax, mediay;
   float correlacion;
   int i;

   for(i=0;i<numero;i++)
   {
	sumax += x[i];
	sumay += y[i];
	sumax2 += x[i]*x[i];
	sumay2 += y[i]*y[i];
	sumaxy += x[i] * y[i];
   }

   mediax = sumax / numero;
   mediay = sumay*sumay / numero;

   *pendiente = (sumaxy - mediax * sumay) / (sumax2 - mediax * sumax);
   *ordenada = (sumay - *pendiente * sumax) / numero;
   *abcisa   = - *ordenada / *pendiente;
   correlacion = (*ordenada * sumay + *pendiente * sumaxy - mediay)
			      / (sumay2 - mediay);
   return(correlacion);
}
