#include <gtk/gtk.h>
#include "checkcopy.h"

gchar *FileName1;
gchar *FileName2;

GtkWidget *g_StrIpt1;
GtkWidget *g_StrIpt2;
GtkWidget *g_StrIpt3;

GtkWidget *g_TxtTst1;
GtkWidget *g_TxtTst2;
GtkWidget *g_TxtTst3;
GtkWidget *g_TxtError;
GtkWidget *g_TxtPercent;

GtkWidget *g_windowErr;
GtkWidget *g_windowAbout;

gboolean on_widget_deleted(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    gtk_widget_hide(widget);
    return TRUE;
}

int main(int argc, char *argv[])
{
    GtkBuilder		*builder; 
	GtkWidget		*window;
	
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
    
///Line Below is i/o
    
    g_StrIpt1 = GTK_WIDGET(gtk_builder_get_object(builder,"StrIpt1"));
	g_StrIpt2 = GTK_WIDGET(gtk_builder_get_object(builder,"StrIpt2"));
	g_StrIpt3 = GTK_WIDGET(gtk_builder_get_object(builder,"StrIpt3"));
    
    g_TxtTst1 = GTK_WIDGET(gtk_builder_get_object(builder,"TxtTst1"));
    g_TxtTst2 = GTK_WIDGET(gtk_builder_get_object(builder,"TxtTst2"));
    g_TxtTst3 = GTK_WIDGET(gtk_builder_get_object(builder,"TxtTst3"));
    g_TxtError = GTK_WIDGET(gtk_builder_get_object(builder,"TxtError"));
	g_TxtPercent = GTK_WIDGET(gtk_builder_get_object(builder,"TxtPercent"));	
	
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    g_windowErr = GTK_WIDGET(gtk_builder_get_object(builder, "window_error"));
    g_windowAbout = GTK_WIDGET(gtk_builder_get_object(builder, "window_about"));
    
    //signal to avoid close button destroying window
    g_signal_connect(G_OBJECT(g_windowErr), "delete-event", G_CALLBACK(on_widget_deleted), NULL);
    g_signal_connect(G_OBJECT(g_windowAbout), "delete-event", G_CALLBACK(on_widget_deleted), NULL);

///Line Above is i/o
    
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();

    return 0;
}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}

//if close button clicked hide window error
void on_BtnErrorClose_clicked(){
	gtk_widget_hide(g_windowErr);
}

//if close button clicked hide window about
void on_BtnAboutClose_clicked(){
	gtk_widget_hide(g_windowAbout);
}

//about window
void on_BtnAboutStatus_clicked(){
	gtk_widget_show(g_windowAbout);
}

//file selector 1
void on_SelFile1_file_set(GtkFileChooser *SelectedFile1){
	FileName1=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(SelectedFile1));
	//printf("%s\n",FileName1); //debug_line_can_be_removed
}

//file selector 2
void on_SelFile2_file_set(GtkFileChooser *SelectedFile2){
	FileName2=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(SelectedFile2));
	//printf("%s\n",FileName2); //debug_line_can_be_removed
}

//button calculate
void on_BtnCalculate_clicked(){
	//some variables
	float Tst1,Tst2,Tst3,Percent,SumMul;
	char HasilS1[10]="\0";
	char HasilS2[10]="\0";
	char HasilS3[10]="\0";
	char PerStr[10]="\0";
	char ErrTxt[50]="\0";
	int ErrStats=0;

	//get value from Mul1-Mul3 and convert to float
	const gchar *MulStr1=gtk_entry_get_text(GTK_ENTRY(g_StrIpt1));
	float Mul1=atof(MulStr1);
	const gchar *MulStr2=gtk_entry_get_text(GTK_ENTRY(g_StrIpt2));
	float Mul2=atof(MulStr2);
	const gchar *MulStr3=gtk_entry_get_text(GTK_ENTRY(g_StrIpt3));
	float Mul3=atof(MulStr3);
	SumMul=Mul1+Mul2+Mul3;
	//printf("%.2f %.2f %.2f %.2f\n",Mul1,Mul2,Mul3,Mul1+Mul2+Mul3); //debug_line_can_be_removed

	//error checker and status
	if(SumMul!=1){
		ErrStats=1;
		strcpy(ErrTxt,"Sum of Multiplier Must Exactly 1");
	}else if(FileName1==NULL){
		ErrStats=2;
		strcpy(ErrTxt,"Select File1 Before Proceeding");
	}else if(FileName2==NULL){
		ErrStats=3;
		strcpy(ErrTxt,"Select File2 Before Proceeding");
	}
	
	if(ErrStats<1){
		//if no error then run all test
		Tst1=test1(FileName1,FileName2,HasilS1);
		Tst2=test2(FileName1,FileName2,HasilS2);
		Tst3=test3(FileName1,FileName2,HasilS3);
		//printf("%s\n%s\n%s\n",hasilS1,hasilS2,hasilS3); //debug_line_can_be_removed
		//calculate final result and convert to string
		Percent=(Tst1*Mul1)+(Tst2*Mul2)+(Tst3*Mul3);
		sprintf(PerStr,"%.2f%%",Percent);
	}else{
		Tst1=0;Tst2=0;Tst3=0;
		strcpy(PerStr,"0.00%");
		strcpy(HasilS1,"0.00%");
		strcpy(HasilS2,"0.00%");
		strcpy(HasilS3,"0.00%");
		gtk_label_set_text(GTK_LABEL(g_TxtError),ErrTxt);
		gtk_widget_show(g_windowErr);
	}
	
	//put all data to GUI
	gtk_label_set_text(GTK_LABEL(g_TxtTst1),HasilS1);
	gtk_label_set_text(GTK_LABEL(g_TxtTst2),HasilS2);
	gtk_label_set_text(GTK_LABEL(g_TxtTst3),HasilS3);
	gtk_label_set_text(GTK_LABEL(g_TxtPercent),PerStr);
}
