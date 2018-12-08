typedef struct PARAM{
	   wchar_t *SadzebniFaili;//=(wchar_t*)malloc(1000);
	   wchar_t * path;//=(wchar_t*)malloc(1000);
	   void constval()
	   {

		  SadzebniFaili =(wchar_t*)malloc(1000);
		  path=(wchar_t*)malloc(1000);
	   }
	   void dconstval()
	   {

		    free(SadzebniFaili);
		    free(path);
	   }

}search;