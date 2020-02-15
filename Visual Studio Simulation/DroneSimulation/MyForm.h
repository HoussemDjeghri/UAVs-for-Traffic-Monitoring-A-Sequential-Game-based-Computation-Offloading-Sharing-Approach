#pragma once

#include <fstream>
#include <iostream>
#include "Tache.h"
#include "Drone.h"
#include "Vehicule.h"
#include "ServeurEdge.h"
#include "Temps.h"
#include "Energie.h"
#include "CoutCalcul.h"
#include "CoutEnvoie.h"
#include "Utilite.h"
#include <map>
#include <string>
#include <map> 
#include <iterator> 
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iomanip>
#include <cmath>
#include <limits>
#define WIN32_LEAN_AND_MEAN

#include <windows.h>



namespace DroneSimulation {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	


	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{

	public:
		

		int E_PC5 = 800; // Energy units consumed by the PC5 interface
		int E_LTEA = 800; // Energy units consumed by the LTE-A / 5G interface
		int Debit_PC5 = 50.4; // transmission rate via PC5 interface in MB/s
		int Debit_LTEA = 50.4; // transmission rate via the LTE-A/5G interface in MB/s
		long double C_LTEA = 0.00000000001; // communication cost of 1 KB via the LTE / 5G interface
		long double C_Calcul_SE = 0.000000000001; // computation cost of 1 KB of data by the Edge server
		long double C_Calcul_VV = 0.0000000000005; // computation cost of 1 KB of data by the neighboring vehicle 
		int QoL = 1; // quality of link  [0,1]  

		//Weighting factors
		long double α = 0.2; // Delay
		long double β = 0.2; // Energy
		long double δ = 0.2; // QoL
		long double γ = 0.2; //CommunicationCost
		long double λ = 0.2; //ComputationCost


		// Quality of link between nodes
		long double QoL_DP_DS = 1;
		long double QoL_DP_SE = 1;
		long double QoL_DP_VP = 1;
		long double QoL_VP_SE = 1;
		long double QoL_VP_VV = 1;


		// Range of size and cycles of data to be processed
		long double cycle_cpu_var = 100000;
		long double max_cycle_cpu_var = 1000000000;
		long double taille_resultat_var = 5;
		long double max_taille_resultat_var = 15;
		long double tailleDonnee_var = 1000;
		long double maxTaille_var = 200000;

		long double PD_cpu_frequency = 12000000000;
		long double NV_cpu_frequency = 36000000000;
		long double AV_cpu_frequency = 60000000000;
		long double ES_cpu_frequency = 600000000000;


		
		
		//Maximum and minimum value of the 5 decision-making factors, its values ​​are used for the normalization of these 5 disjoint factors, its values ​​are recalculated at the start of the simulation
		long double maxT = 0;
		long double minT = 20000000000000;
		long double maxE = 0;
		long double minE = 20000000000000;
		long double maxCE = 0;
		long double minCE = 20000000000000;
		long double maxCC = 0;
		long double minCC = 20000000000000;

		bool calculer_limites = true; // variable to indicate to the program if it has to recalculate the limits of the parameters (max-min), if the limits are to be set manually.

	private: System::Windows::Forms::Label^  label26;
	
	private: System::Windows::Forms::TextBox^  textBox23;
			 bool envoi_et_calcul_gratuit = false; // variable to indicate that the sending and calculation of the data is free, it is used to avoid an arethmustic exception when the currency is set to 0 in case the cost is set to 0


	public:
		MyForm(void)
		{
			InitializeComponent();
			this->textBox1->Text = E_PC5.ToString();
			this->textBox2->Text = C_LTEA.ToString();
			this->textBox3->Text = C_Calcul_SE.ToString();
			this->textBox4->Text = E_LTEA.ToString();
			this->textBox5->Text = C_Calcul_VV.ToString();
			this->textBox6->Text = Debit_PC5.ToString();
			this->textBox7->Text = QoL.ToString();
			this->textBox8->Text = Debit_LTEA.ToString();
			this->textBox9->Text = α.ToString();
			this->textBox10->Text = β.ToString();
			this->textBox11->Text = γ.ToString();
			this->textBox12->Text = cycle_cpu_var.ToString();
			this->textBox13->Text = λ.ToString();
			this->textBox14->Text = tailleDonnee_var.ToString();
			this->textBox15->Text = max_cycle_cpu_var.ToString();
			this->textBox16->Text = maxTaille_var.ToString();
			this->textBox17->Text = taille_resultat_var.ToString();
			this->textBox18->Text = max_taille_resultat_var.ToString();
			this->textBox19->Text = PD_cpu_frequency.ToString();
			this->textBox20->Text = AV_cpu_frequency.ToString();
			this->textBox21->Text = NV_cpu_frequency.ToString();
			this->textBox22->Text = ES_cpu_frequency.ToString();
			this->textBox23->Text = δ.ToString();
			
			
			
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  panel1;
	protected:
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox8;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::TextBox^  textBox13;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::TextBox^  textBox11;
	private: System::Windows::Forms::TextBox^  textBox10;
	private: System::Windows::Forms::TextBox^  textBox9;
	private: System::Windows::Forms::Panel^  panel3;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::TextBox^  textBox18;
	private: System::Windows::Forms::TextBox^  textBox17;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::TextBox^  textBox16;
	private: System::Windows::Forms::TextBox^  textBox15;
	private: System::Windows::Forms::TextBox^  textBox14;
	private: System::Windows::Forms::TextBox^  textBox12;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::Panel^  panel4;
	private: System::Windows::Forms::Label^  label25;
	private: System::Windows::Forms::Label^  label24;
	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::Label^  label22;
	private: System::Windows::Forms::TextBox^  textBox22;
	private: System::Windows::Forms::TextBox^  textBox21;
	private: System::Windows::Forms::TextBox^  textBox20;
	private: System::Windows::Forms::TextBox^  textBox19;
	private: System::Windows::Forms::Button^  button1;










	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->textBox23 = (gcnew System::Windows::Forms::TextBox());
			this->textBox13 = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->textBox18 = (gcnew System::Windows::Forms::TextBox());
			this->textBox17 = (gcnew System::Windows::Forms::TextBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->textBox16 = (gcnew System::Windows::Forms::TextBox());
			this->textBox15 = (gcnew System::Windows::Forms::TextBox());
			this->textBox14 = (gcnew System::Windows::Forms::TextBox());
			this->textBox12 = (gcnew System::Windows::Forms::TextBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->textBox22 = (gcnew System::Windows::Forms::TextBox());
			this->textBox21 = (gcnew System::Windows::Forms::TextBox());
			this->textBox20 = (gcnew System::Windows::Forms::TextBox());
			this->textBox19 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panel3->SuspendLayout();
			this->panel4->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::ControlLight;
			this->panel1->Controls->Add(this->label9);
			this->panel1->Controls->Add(this->label8);
			this->panel1->Controls->Add(this->label7);
			this->panel1->Controls->Add(this->label6);
			this->panel1->Controls->Add(this->label5);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->textBox8);
			this->panel1->Controls->Add(this->textBox7);
			this->panel1->Controls->Add(this->textBox6);
			this->panel1->Controls->Add(this->textBox5);
			this->panel1->Controls->Add(this->textBox4);
			this->panel1->Controls->Add(this->textBox3);
			this->panel1->Controls->Add(this->textBox2);
			this->panel1->Controls->Add(this->textBox1);
			this->panel1->Location = System::Drawing::Point(12, 549);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(728, 159);
			this->panel1->TabIndex = 0;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->BackColor = System::Drawing::Color::Transparent;
			this->label9->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(462, 125);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(121, 16);
			this->label9->TabIndex = 16;
			this->label9->Text = L"Quality Of Link [0,1]*:";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->BackColor = System::Drawing::Color::Transparent;
			this->label8->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(372, 90);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(211, 16);
			this->label8->TabIndex = 15;
			this->label8->Text = L"Computation Cost Nearby Vehicule*:";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::Color::Transparent;
			this->label7->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(392, 53);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(191, 16);
			this->label7->TabIndex = 14;
			this->label7->Text = L"Computation Cost Edge Server*:";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::Color::Transparent;
			this->label6->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(413, 16);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(170, 16);
			this->label6->TabIndex = 13;
			this->label6->Text = L"Communication Cost LTE-A*:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(83, 124);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(119, 16);
			this->label5->TabIndex = 12;
			this->label5->Text = L"LTE-A Throughput*:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(94, 89);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(107, 16);
			this->label4->TabIndex = 11;
			this->label4->Text = L"PC5 Throughput*:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(30, 51);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(172, 16);
			this->label3->TabIndex = 10;
			this->label3->Text = L"LTE-A Energy Consumption*:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(42, 16);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(160, 16);
			this->label2->TabIndex = 9;
			this->label2->Text = L"PC5 Energy Consumption*:";
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(202, 123);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(126, 20);
			this->textBox8->TabIndex = 8;
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(583, 124);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(126, 20);
			this->textBox7->TabIndex = 7;
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(202, 88);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(126, 20);
			this->textBox6->TabIndex = 6;
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(583, 88);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(126, 20);
			this->textBox5->TabIndex = 5;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(202, 50);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(126, 20);
			this->textBox4->TabIndex = 4;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(583, 52);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(126, 20);
			this->textBox3->TabIndex = 3;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(583, 15);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(126, 20);
			this->textBox2->TabIndex = 2;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(202, 16);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(126, 20);
			this->textBox1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(15, 171);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(226, 25);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Simulation Parameters";
			this->label1->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label14->Location = System::Drawing::Point(18, 197);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(328, 16);
			this->label14->TabIndex = 27;
			this->label14->Text = L"Simulation parameters can be kept by default or modified";
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::SystemColors::ControlLight;
			this->panel2->Controls->Add(this->label26);
			this->panel2->Controls->Add(this->textBox23);
			this->panel2->Controls->Add(this->textBox13);
			this->panel2->Controls->Add(this->label13);
			this->panel2->Controls->Add(this->label12);
			this->panel2->Controls->Add(this->label11);
			this->panel2->Controls->Add(this->label10);
			this->panel2->Controls->Add(this->textBox11);
			this->panel2->Controls->Add(this->textBox10);
			this->panel2->Controls->Add(this->textBox9);
			this->panel2->Location = System::Drawing::Point(12, 426);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(728, 117);
			this->panel2->TabIndex = 28;
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label26->Location = System::Drawing::Point(3, 76);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(199, 16);
			this->label26->TabIndex = 36;
			this->label26->Text = L"Qualtiy Of Link Weighting factor(δ):";
			// 
			// textBox23
			// 
			this->textBox23->Location = System::Drawing::Point(202, 75);
			this->textBox23->Name = L"textBox23";
			this->textBox23->Size = System::Drawing::Size(126, 20);
			this->textBox23->TabIndex = 35;
			// 
			// textBox13
			// 
			this->textBox13->Location = System::Drawing::Point(583, 45);
			this->textBox13->Name = L"textBox13";
			this->textBox13->Size = System::Drawing::Size(126, 20);
			this->textBox13->TabIndex = 34;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label13->Location = System::Drawing::Point(339, 46);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(243, 16);
			this->label13->TabIndex = 33;
			this->label13->Text = L"Communication Cost weighting factor (λ)*:";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(339, 16);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(243, 16);
			this->label12->TabIndex = 32;
			this->label12->Text = L"Communication Cost weighting factor (γ)*:";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->Location = System::Drawing::Point(32, 45);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(168, 16);
			this->label11->TabIndex = 31;
			this->label11->Text = L"Energy weighting factor (β)*:";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(40, 15);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(160, 16);
			this->label10->TabIndex = 30;
			this->label10->Text = L"Delay weighting factor (α)*:";
			// 
			// textBox11
			// 
			this->textBox11->Location = System::Drawing::Point(583, 14);
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(126, 20);
			this->textBox11->TabIndex = 29;
			// 
			// textBox10
			// 
			this->textBox10->Location = System::Drawing::Point(202, 44);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(126, 20);
			this->textBox10->TabIndex = 28;
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(202, 15);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(126, 20);
			this->textBox9->TabIndex = 27;
			// 
			// panel3
			// 
			this->panel3->BackColor = System::Drawing::SystemColors::ControlLight;
			this->panel3->Controls->Add(this->label20);
			this->panel3->Controls->Add(this->label19);
			this->panel3->Controls->Add(this->textBox18);
			this->panel3->Controls->Add(this->textBox17);
			this->panel3->Controls->Add(this->label18);
			this->panel3->Controls->Add(this->label17);
			this->panel3->Controls->Add(this->label16);
			this->panel3->Controls->Add(this->label15);
			this->panel3->Controls->Add(this->textBox16);
			this->panel3->Controls->Add(this->textBox15);
			this->panel3->Controls->Add(this->textBox14);
			this->panel3->Controls->Add(this->textBox12);
			this->panel3->Location = System::Drawing::Point(12, 311);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(728, 109);
			this->panel3->TabIndex = 29;
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label20->Location = System::Drawing::Point(529, 76);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(55, 16);
			this->label20->TabIndex = 11;
			this->label20->Text = L"max Ri*:";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label19->Location = System::Drawing::Point(151, 75);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(51, 16);
			this->label19->TabIndex = 10;
			this->label19->Text = L"min Ri*:";
			// 
			// textBox18
			// 
			this->textBox18->Location = System::Drawing::Point(584, 76);
			this->textBox18->Name = L"textBox18";
			this->textBox18->Size = System::Drawing::Size(126, 20);
			this->textBox18->TabIndex = 9;
			// 
			// textBox17
			// 
			this->textBox17->Location = System::Drawing::Point(203, 74);
			this->textBox17->Name = L"textBox17";
			this->textBox17->Size = System::Drawing::Size(126, 20);
			this->textBox17->TabIndex = 8;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label18->Location = System::Drawing::Point(527, 47);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(56, 16);
			this->label18->TabIndex = 7;
			this->label18->Text = L"max Di*:";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label17->Location = System::Drawing::Point(529, 16);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(55, 16);
			this->label17->TabIndex = 6;
			this->label17->Text = L"max Ci*:";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label16->Location = System::Drawing::Point(151, 45);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(52, 16);
			this->label16->TabIndex = 5;
			this->label16->Text = L"min Di*:";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label15->Location = System::Drawing::Point(152, 14);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(51, 16);
			this->label15->TabIndex = 4;
			this->label15->Text = L"min Ci*:";
			// 
			// textBox16
			// 
			this->textBox16->Location = System::Drawing::Point(584, 46);
			this->textBox16->Name = L"textBox16";
			this->textBox16->Size = System::Drawing::Size(126, 20);
			this->textBox16->TabIndex = 3;
			// 
			// textBox15
			// 
			this->textBox15->Location = System::Drawing::Point(584, 16);
			this->textBox15->Name = L"textBox15";
			this->textBox15->Size = System::Drawing::Size(126, 20);
			this->textBox15->TabIndex = 2;
			// 
			// textBox14
			// 
			this->textBox14->Location = System::Drawing::Point(203, 45);
			this->textBox14->Name = L"textBox14";
			this->textBox14->Size = System::Drawing::Size(126, 20);
			this->textBox14->TabIndex = 1;
			// 
			// textBox12
			// 
			this->textBox12->Location = System::Drawing::Point(203, 14);
			this->textBox12->Name = L"textBox12";
			this->textBox12->Size = System::Drawing::Size(126, 20);
			this->textBox12->TabIndex = 0;
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"Century Gothic", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label21->Location = System::Drawing::Point(56, 9);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(644, 99);
			this->label21->TabIndex = 30;
			this->label21->Text = L"UAVs for Traffic Monitoring : A Sequential \r\nGame based Computation Offloading/ S"
				L"haring \r\nApproach - Algorithm Simulation\r\n";
			this->label21->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// panel4
			// 
			this->panel4->BackColor = System::Drawing::SystemColors::ControlLight;
			this->panel4->Controls->Add(this->label25);
			this->panel4->Controls->Add(this->label24);
			this->panel4->Controls->Add(this->label23);
			this->panel4->Controls->Add(this->label22);
			this->panel4->Controls->Add(this->textBox22);
			this->panel4->Controls->Add(this->textBox21);
			this->panel4->Controls->Add(this->textBox20);
			this->panel4->Controls->Add(this->textBox19);
			this->panel4->ForeColor = System::Drawing::SystemColors::ControlText;
			this->panel4->Location = System::Drawing::Point(12, 220);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(728, 85);
			this->panel4->TabIndex = 31;
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label25->Location = System::Drawing::Point(403, 55);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(178, 16);
			this->label25->TabIndex = 7;
			this->label25->Text = L"Edge Server CPU Frequency*:";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label24->Location = System::Drawing::Point(382, 20);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(198, 16);
			this->label24->TabIndex = 6;
			this->label24->Text = L"Nearby Vehicule CPU Frequency*:";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label23->Location = System::Drawing::Point(11, 53);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(189, 16);
			this->label23->TabIndex = 5;
			this->label23->Text = L"Authority CPU Frequency (Ghz)*:";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label22->Location = System::Drawing::Point(40, 15);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(161, 16);
			this->label22->TabIndex = 4;
			this->label22->Text = L"UAV CPU Frequency (Ghz)*:";
			// 
			// textBox22
			// 
			this->textBox22->Location = System::Drawing::Point(581, 53);
			this->textBox22->Name = L"textBox22";
			this->textBox22->Size = System::Drawing::Size(126, 20);
			this->textBox22->TabIndex = 3;
			// 
			// textBox21
			// 
			this->textBox21->Location = System::Drawing::Point(581, 19);
			this->textBox21->Name = L"textBox21";
			this->textBox21->Size = System::Drawing::Size(126, 20);
			this->textBox21->TabIndex = 2;
			// 
			// textBox20
			// 
			this->textBox20->Location = System::Drawing::Point(201, 53);
			this->textBox20->Name = L"textBox20";
			this->textBox20->Size = System::Drawing::Size(125, 20);
			this->textBox20->TabIndex = 1;
			// 
			// textBox19
			// 
			this->textBox19->Location = System::Drawing::Point(201, 15);
			this->textBox19->Name = L"textBox19";
			this->textBox19->Size = System::Drawing::Size(126, 20);
			this->textBox19->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Bahnschrift", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(305, 727);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(141, 39);
			this->button1->TabIndex = 32;
			this->button1->Text = L"Launch Simulation";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(753, 787);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->panel4);
			this->Controls->Add(this->label21);
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->label1);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(769, 826);
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(769, 826);
			this->Name = L"MyForm";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"UAVs for Traffic Monitoring : Algorithm Simulation";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion



	 


	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		
		
		E_PC5 = Double::Parse(this->textBox1->Text);
		C_LTEA= Double::Parse(this->textBox2->Text );
		C_Calcul_SE =Double::Parse(this->textBox3->Text);
		E_LTEA =Double::Parse(this->textBox4->Text); 
		C_Calcul_VV =Double::Parse(this->textBox5->Text); 
		Debit_PC5 =Double::Parse(this->textBox6->Text);
		QoL =Double::Parse(this->textBox7->Text); 
		Debit_LTEA =Double::Parse(this->textBox8->Text); 
		α =Double::Parse(this->textBox9->Text); 
		β =Double::Parse(this->textBox10->Text); 
		γ =Double::Parse(this->textBox11->Text); 
		cycle_cpu_var =Double::Parse(this->textBox12->Text);
		λ =Double::Parse(this->textBox13->Text); 
		tailleDonnee_var =Double::Parse(this->textBox14->Text); 
		max_cycle_cpu_var =Double::Parse(this->textBox15->Text); 
		maxTaille_var =Double::Parse(this->textBox16->Text);
		taille_resultat_var =Double::Parse(this->textBox17->Text); 
		max_taille_resultat_var =Double::Parse(this->textBox18->Text); 
		PD_cpu_frequency =Double::Parse(this->textBox19->Text); 
		AV_cpu_frequency =Double::Parse(this->textBox20->Text);
		NV_cpu_frequency =Double::Parse(this->textBox21->Text); 
		ES_cpu_frequency =Double::Parse(this->textBox22->Text); 
		δ =Double::Parse(this->textBox23->Text);



		std::vector <Tache> taches; // matrix containing the tasks to be calculated with the decision to be taken for each task  
		std::vector <Drone> drones_secondaires;
		Drone drone_pricipal(1, 100, PD_cpu_frequency);
		Vehicule vehicule_police(1, AV_cpu_frequency, 0);
		Vehicule vehicule_voisin(2, NV_cpu_frequency, 0);
		ServeurEdge serveur_edge(1, ES_cpu_frequency);
		std::map < int, long double > utilites_Local; // matrix for storing the local computation utility in the main UAV for each task
		std::map < int, long double > utilites_Delestage_SE;// matrix to store the utility of the load shedding of the computation to the ES for each task
		std::map < int, long double > utilites_Partage_DS;// matrix to store the utility of sharing with SD for each task
		std::map < int, long double > utilites_Local_VP;// Matrix for storing the usefulness of local calculation in the authority vehicle for each task
		std::map < int, long double > utilites_VP_Delestage_SE;// matrice pour stocker l'utilité du délestage vers SE par le VP pour chaque tache
		std::map < int, long double > utilites_VP_Partage_VV_accpt;// matrix to store the utility of load shedding to ES by the AV for each task
		std::map < int, long double > utilites_VP_Partage_VV_refu;//  Matrix for storing the usefulness of the refusal of the calculation by the nearby vehicles for each task




		for (int j = 2; j < 4; j++)
		{
			Drone drone_secondaire(j, 100, PD_cpu_frequency);
			drones_secondaires.push_back(drone_secondaire);
		}

		if (calculer_limites) {
			calibrer_limites(drone_pricipal, serveur_edge, vehicule_police, vehicule_voisin, drones_secondaires,taches, utilites_Local, utilites_Delestage_SE, utilites_Partage_DS, utilites_Local_VP, utilites_VP_Delestage_SE, utilites_VP_Partage_VV_accpt, utilites_VP_Partage_VV_refu);
			calculer_limites = false;
		}
		std::cout << "///////////////////////////////////////////////SIMULATION START/////////////////////////////////////////////////////";
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//SIMULATION n°1 = calculation of the global utility, the energy, and the delay for each strategy in relation to the change of the CPU Cycles of the tasks    
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Assignment of intervals of data size and complexity
		long double cycle_cpu = cycle_cpu_var;
		long double max_cycle_cpu = max_cycle_cpu_var;
		long double taille_resultat = taille_resultat_var;
		long double tailleDonnee = tailleDonnee_var;
		long double maxTaille = maxTaille_var;

		int iter = 1;
		// matrix to store the usefulness of each strategy+GT according to the CPU cycle change  [CPU_Cycle, [U1,U2,U3,U4,U5,U6,U7,GT]] 
		std::map<long double, Utilite> utilites_CPU;
		// matrix to store the energy of each strategy+GT according to the CPU cycle change   [CPU_Cycle, [U1,U2,U3,U4,U5,U6,U7,GT]] 
		std::map<long double, Energie> energies_CPU;
		// matrix to store the time of each strategy+GT according to the CPU cycle change  [CPU_Cycle, [U1,U2,U3,U4,U5,U6,U7,GT]] 
		std::map<long double, Temps> temps_CPU;
		// matrix to store the dispatch cost of each strategy+GT according to the CPU cycle change  [CPU_Cycle, [U1,U2,U3,U4,U5,U6,U7,GT]] 
		std::map<long double, CoutEnvoie> coutEnvoi_CPU;
		// matrix to store the calculation cost of each strategy+GT according to the CPU cycle change  [CPU_Cycle, [U1,U2,U3,U4,U5,U6,U7,GT]] 
		std::map<long double, CoutCalcul> coutCalcul_CPU;
		while (tailleDonnee <= maxTaille)
		{
			int i = 0;
			taches.clear();

			while (cycle_cpu <= max_cycle_cpu)
			{
				Tache tachei(i, cycle_cpu, tailleDonnee, taille_resultat, 1);
				taches.push_back(tachei);
				cycle_cpu = cycle_cpu * 2;
				i++;
			}



			std::multimap < int, Tache> ::iterator itr;
			int meilleurStrategie;
			long double meilleurUtilite;
			long double meilleurEnergie;
			long double meilleurTemps;
			long double meilleurCoutEnvoi;
			long double meilleurCoutCalcul;
			long double temp_util = 0;
			long double temp_energ = 0;
			long double temp_temps = 0;
			long double temp_ce = 0;
			long double temp_cc = 0;
			for (int c = 0; c < taches.size(); c++)
			{
				Utilite temp_util_obj;
				Energie temp_ener_obj;
				Temps temp_temps_obj;
				CoutEnvoie temp_ce_obj;
				CoutCalcul temp_cc_obj;
				Tache ti = taches[c];
				meilleurStrategie = 1;
				meilleurUtilite = 0;
				meilleurEnergie = 0;
				meilleurTemps = 0;
				meilleurCoutEnvoi = 0;
				meilleurCoutCalcul = 0;

				///////////////////// S1 : local computation //////////////////////////////////////
				temp_util = calcul_local_DP(ti, drone_pricipal);
				temp_energ = getEnergieS1(ti, drone_pricipal);
				temp_temps = getTempsS1(ti, drone_pricipal);
				temp_ce = getCES1(ti);
				temp_cc = getCCS1(ti);
				if (iter == 1) {
					temp_util_obj.setU1(temp_util);
					temp_ener_obj.setE1(temp_energ);
					temp_temps_obj.setT1(temp_temps);
					temp_ce_obj.setCE1(temp_ce);
					temp_cc_obj.setCC1(temp_cc);
				}
				else {

					utilites_CPU[ti.getCi()].setU1(utilites_CPU[ti.getCi()].getU1() + temp_util);
					energies_CPU[ti.getCi()].setE1(energies_CPU[ti.getCi()].getE1() + temp_energ);
					temps_CPU[ti.getCi()].setT1(temps_CPU[ti.getCi()].getT1() + temp_temps);
					coutEnvoi_CPU[ti.getCi()].setCE1(coutEnvoi_CPU[ti.getCi()].getCE1() + temp_ce);
					coutCalcul_CPU[ti.getCi()].setCC1(coutCalcul_CPU[ti.getCi()].getCC1() + temp_cc);
				}

				utilites_Local.insert(std::pair<int, long double>(ti.getId(), temp_util));
				meilleurUtilite = temp_util;
				meilleurEnergie = temp_energ;
				meilleurTemps = temp_temps;
				meilleurCoutEnvoi = temp_ce;
				meilleurCoutCalcul = temp_cc;

				//////////////////////// S2 : offloading to Edge server//////////////////////////
				temp_util = calcul_delestage_SE(ti, serveur_edge);
				temp_energ = getEnergieS2(ti);
				temp_temps = getTempsS2(ti, serveur_edge);
				temp_ce = getCES2(ti);
				temp_cc = getCCS2(ti);
				if (iter == 1) {
					temp_util_obj.setU2(temp_util);
					temp_ener_obj.setE2(temp_energ);
					temp_temps_obj.setT2(temp_temps);
					temp_ce_obj.setCE2(temp_ce);
					temp_cc_obj.setCC2(temp_cc);
				}
				else {

					utilites_CPU[ti.getCi()].setU2(utilites_CPU[ti.getCi()].getU2() + temp_util);
					energies_CPU[ti.getCi()].setE2(energies_CPU[ti.getCi()].getE2() + temp_energ);
					temps_CPU[ti.getCi()].setT2(temps_CPU[ti.getCi()].getT2() + temp_temps);
					coutEnvoi_CPU[ti.getCi()].setCE2(coutEnvoi_CPU[ti.getCi()].getCE2() + temp_ce);
					coutCalcul_CPU[ti.getCi()].setCC2(coutCalcul_CPU[ti.getCi()].getCC2() + temp_cc);
				}

				utilites_Delestage_SE.insert(std::pair<int, long double>(ti.getId(), temp_util));

				if (temp_util < meilleurUtilite) {
					meilleurStrategie = 2;
					meilleurUtilite = temp_util;
					meilleurEnergie = temp_energ;
					meilleurTemps = temp_temps;
					meilleurCoutEnvoi = temp_ce;
					meilleurCoutCalcul = temp_cc;
				}

				///////////////////////////////////// S3 : sharing with secondary drones///////////////////////////////////////////
				temp_util = calcul_partage_DS(ti, drone_pricipal, drones_secondaires);
				temp_energ = getEnergieS3(ti, drone_pricipal, drones_secondaires);
				temp_temps = getTempsS3(ti, drone_pricipal, drones_secondaires);
				temp_ce = getCES3(ti);
				temp_cc = getCCS3(ti);
				if (iter == 1) {
					temp_util_obj.setU3(temp_util);
					temp_ener_obj.setE3(temp_energ);
					temp_temps_obj.setT3(temp_temps);
					temp_ce_obj.setCE3(temp_ce);
					temp_cc_obj.setCC3(temp_cc);
				}
				else {

					utilites_CPU[ti.getCi()].setU3(utilites_CPU[ti.getCi()].getU3() + temp_util);
					energies_CPU[ti.getCi()].setE3(energies_CPU[ti.getCi()].getE3() + temp_energ);
					temps_CPU[ti.getCi()].setT3(temps_CPU[ti.getCi()].getT3() + temp_temps);
					coutEnvoi_CPU[ti.getCi()].setCE3(coutEnvoi_CPU[ti.getCi()].getCE3() + temp_ce);
					coutCalcul_CPU[ti.getCi()].setCC3(coutCalcul_CPU[ti.getCi()].getCC3() + temp_cc);
				}

				utilites_Partage_DS.insert(std::pair<int, long double>(ti.getId(), temp_util));
				if (temp_util < meilleurUtilite) {
					meilleurStrategie = 3;
					meilleurUtilite = temp_util;
					meilleurEnergie = temp_energ;
					meilleurTemps = temp_temps;
					meilleurCoutEnvoi = temp_ce;
					meilleurCoutCalcul = temp_cc;
				}

				////////////////////////////////////////////S4 : offloading to authority  vehicle + local computation in authority vehicle//////////////////////////////////////////////
				temp_util = calcul_local_VP(ti, vehicule_police);
				temp_energ = getEnergieS4(ti, vehicule_police);
				temp_temps = getTempsS4(ti, vehicule_police);
				temp_ce = getCES4(ti);
				temp_cc = getCCS4(ti);
				if (iter == 1) {
					temp_util_obj.setU4(temp_util);
					temp_ener_obj.setE4(temp_energ);
					temp_temps_obj.setT4(temp_temps);
					temp_ce_obj.setCE4(temp_ce);
					temp_cc_obj.setCC4(temp_cc);
				}
				else {

					utilites_CPU[ti.getCi()].setU4(utilites_CPU[ti.getCi()].getU4() + temp_util);
					energies_CPU[ti.getCi()].setE4(energies_CPU[ti.getCi()].getE4() + temp_energ);
					temps_CPU[ti.getCi()].setT4(temps_CPU[ti.getCi()].getT4() + temp_temps);
					coutEnvoi_CPU[ti.getCi()].setCE4(coutEnvoi_CPU[ti.getCi()].getCE4() + temp_ce);
					coutCalcul_CPU[ti.getCi()].setCC4(coutCalcul_CPU[ti.getCi()].getCC4() + temp_cc);
				}

				utilites_Local_VP.insert(std::pair<int, long double>(ti.getId(), temp_util));
				if (temp_util < meilleurUtilite) {
					meilleurStrategie = 4;
					meilleurUtilite = temp_util;
					meilleurEnergie = temp_energ;
					meilleurTemps = temp_temps;
					meilleurCoutEnvoi = temp_ce;
					meilleurCoutCalcul = temp_cc;
				}

				/////////////////////////////////////// S5 : offloading to authority vehicle + offloading to Edge server by the authority vehicle////////////////////////////////////////////////
				temp_util = calcul_delestage_VP_SE(ti, serveur_edge);
				temp_energ = getEnergieS5(ti);
				temp_temps = getTempsS5(ti, serveur_edge);
				temp_ce = getCES5(ti);
				temp_cc = getCCS5(ti);
				if (iter == 1) {
					temp_util_obj.setU5(temp_util);
					temp_ener_obj.setE5(temp_energ);
					temp_temps_obj.setT5(temp_temps);
					temp_ce_obj.setCE5(temp_ce);
					temp_cc_obj.setCC5(temp_cc);
				}
				else {

					utilites_CPU[ti.getCi()].setU5(utilites_CPU[ti.getCi()].getU5() + temp_util);
					energies_CPU[ti.getCi()].setE5(energies_CPU[ti.getCi()].getE5() + temp_energ);
					temps_CPU[ti.getCi()].setT5(temps_CPU[ti.getCi()].getT5() + temp_temps);
					coutEnvoi_CPU[ti.getCi()].setCE5(coutEnvoi_CPU[ti.getCi()].getCE5() + temp_ce);
					coutCalcul_CPU[ti.getCi()].setCC5(coutCalcul_CPU[ti.getCi()].getCC5() + temp_cc);
				}

				utilites_VP_Delestage_SE.insert(std::pair<int, long double>(ti.getId(), temp_util));
				if (temp_util < meilleurUtilite) {
					meilleurStrategie = 5;
					meilleurUtilite = temp_util;
					meilleurEnergie = temp_energ;
					meilleurTemps = temp_temps;
					meilleurCoutEnvoi = temp_ce;
					meilleurCoutCalcul = temp_cc;
				}
				////////////////////////////////////// S6 : offloading to authority vehicle + sharing with nearby vehicle + accpet computation by nearby vehicle//////////////////////////////////////////
				temp_util = calcul_partage_VV_accpt(ti, vehicule_police, vehicule_voisin);
				temp_energ = getEnergieS6(ti, vehicule_police, vehicule_voisin);
				temp_temps = getTempsS6(ti, vehicule_voisin);
				temp_ce = getCES6(ti);
				temp_cc = getCCS6(ti);
				if (iter == 1) {
					temp_util_obj.setU6(temp_util);
					temp_ener_obj.setE6(temp_energ);
					temp_temps_obj.setT6(temp_temps);
					temp_ce_obj.setCE6(temp_ce);
					temp_cc_obj.setCC6(temp_cc);
				}
				else {

					utilites_CPU[ti.getCi()].setU6(utilites_CPU[ti.getCi()].getU6() + temp_util);
					energies_CPU[ti.getCi()].setE6(energies_CPU[ti.getCi()].getE6() + temp_energ);
					temps_CPU[ti.getCi()].setT6(temps_CPU[ti.getCi()].getT6() + temp_temps);
					coutEnvoi_CPU[ti.getCi()].setCE6(coutEnvoi_CPU[ti.getCi()].getCE6() + temp_ce);
					coutCalcul_CPU[ti.getCi()].setCC6(coutCalcul_CPU[ti.getCi()].getCC6() + temp_cc);
				}

				utilites_VP_Partage_VV_accpt.insert(std::pair<int, long double>(ti.getId(), temp_util));
				if (temp_util < meilleurUtilite) {
					meilleurStrategie = 6;
					meilleurUtilite = temp_util;
					meilleurEnergie = temp_energ;
					meilleurTemps = temp_temps;
					meilleurCoutEnvoi = temp_ce;
					meilleurCoutCalcul = temp_cc;
				}
				////////////////////////////////////////////S7 : offloading to authority vehicle + sharing with nearby vehicle + refuse computation by nearby vehicle//////////////////////////////////////////
				temp_util = calcul_partage_VV_refu(ti, vehicule_police);
				temp_energ = getEnergieS7(ti, vehicule_police);
				temp_temps = getTempsS7(ti, vehicule_police);
				temp_ce = getCES7(ti);
				temp_cc = getCCS7(ti);
				if (iter == 1) {
					temp_util_obj.setU7(temp_util);
					temp_ener_obj.setE7(temp_energ);
					temp_temps_obj.setT7(temp_temps);
					temp_ce_obj.setCE7(temp_ce);
					temp_cc_obj.setCC7(temp_cc);

				}
				else {

					utilites_CPU[ti.getCi()].setU7(utilites_CPU[ti.getCi()].getU7() + temp_util);
					energies_CPU[ti.getCi()].setE7(energies_CPU[ti.getCi()].getE7() + temp_energ);
					temps_CPU[ti.getCi()].setT7(temps_CPU[ti.getCi()].getT7() + temp_temps);
					coutEnvoi_CPU[ti.getCi()].setCE7(coutEnvoi_CPU[ti.getCi()].getCE7() + temp_ce);
					coutCalcul_CPU[ti.getCi()].setCC7(coutCalcul_CPU[ti.getCi()].getCC7() + temp_cc);
				}

				utilites_VP_Partage_VV_refu.insert(std::pair<int, long double>(ti.getId(), temp_util));
				if (temp_util < meilleurUtilite) {
					meilleurStrategie = 7;
					meilleurUtilite = temp_util;
					meilleurEnergie = temp_energ;
					meilleurTemps = temp_temps;
					meilleurCoutEnvoi = temp_ce;
					meilleurCoutCalcul = temp_cc;
				}

				if (iter == 1) {
					temp_util_obj.setGt(meilleurUtilite);
					temp_ener_obj.setGt(meilleurEnergie);
					temp_temps_obj.setGt(meilleurTemps);
					temp_ce_obj.setGt(meilleurCoutEnvoi);
					temp_cc_obj.setGt(meilleurCoutCalcul);
				}
				else {

					utilites_CPU[ti.getCi()].setGt(utilites_CPU[ti.getCi()].getGt() + meilleurUtilite);
					energies_CPU[ti.getCi()].setGt(energies_CPU[ti.getCi()].getGt() + meilleurEnergie);
					temps_CPU[ti.getCi()].setGt(temps_CPU[ti.getCi()].getGt() + meilleurTemps);
					coutEnvoi_CPU[ti.getCi()].setGt(coutEnvoi_CPU[ti.getCi()].getGt() + meilleurCoutEnvoi);
					coutCalcul_CPU[ti.getCi()].setGt(coutCalcul_CPU[ti.getCi()].getGt() + meilleurCoutCalcul);
				}

				if (iter == 1) {
					utilites_CPU.insert(std::pair<long double, Utilite>(ti.getCi(), temp_util_obj));
					energies_CPU.insert(std::pair<long double, Energie>(ti.getCi(), temp_ener_obj));
					temps_CPU.insert(std::pair<long double, Temps>(ti.getCi(), temp_temps_obj));
					coutEnvoi_CPU.insert(std::pair<long double, CoutEnvoie>(ti.getCi(), temp_ce_obj));
					coutCalcul_CPU.insert(std::pair<long double, CoutCalcul>(ti.getCi(), temp_cc_obj));
				}

				tailleDonnee = tailleDonnee * 2;
				std::cout << "Tache num " << ti.getId() << "Ci" << ti.getCi() << " U1  " << utilites_CPU[ti.getCi()].getU1() << " U2 " << utilites_CPU[ti.getCi()].getU2() << " U3 " << utilites_CPU[ti.getCi()].getU3() << " U4 " << utilites_CPU[ti.getCi()].getU4() << " U5 " << utilites_CPU[ti.getCi()].getU5() << " U6 " << utilites_CPU[ti.getCi()].getU6() << "U7 " << utilites_CPU[ti.getCi()].getU7() << "Meuilleur S" << utilites_CPU[ti.getCi()].getGt() << '\n';
				//cout << "Tache num " << ti.getId() << " Ci: " << ti.getCi() << " Di: " << ti.getDi() << " CE1  " << coutEnvoi_CPU[ti.getCi()].getCE1() << " CE2 " << coutEnvoi_CPU[ti.getCi()].getCE2() << " CE3 " << coutEnvoi_CPU[ti.getCi()].getCE3() << " CE4 " << coutEnvoi_CPU[ti.getCi()].getCE4() << " U5 " << utilites_Donnees[ti.getDi()].getU5() << " U6 " << utilites_Donnees[ti.getDi()].getU6() << "U7 " << utilites_Donnees[ti.getDi()].getU7() << "Meuilleur S" << meilleurStrategie << '\n';
			}


			iter++;




			cycle_cpu = cycle_cpu_var;
			tailleDonnee = tailleDonnee * 2;
		}

		/////////Calculation of the average utility of each strategy

		long double total_U1 = 0;
		long double total_U2 = 0;
		long double total_U3 = 0;
		long double total_U4 = 0;
		long double total_U5 = 0;
		long double total_U6 = 0;
		long double total_U7 = 0;
		long double total_Gt = 0;

		std::map<long double, Utilite>::iterator it1;


		int nb_util_cpu = 0;
		for (it1 = utilites_CPU.begin(); it1 != utilites_CPU.end(); it1++)
		{
			total_U1 = total_U1 + it1->second.getU1() / iter;
			total_U2 = total_U2 + it1->second.getU2() / iter;
			total_U3 = total_U3 + it1->second.getU3() / iter;
			total_U4 = total_U4 + it1->second.getU4() / iter;
			total_U5 = total_U5 + it1->second.getU5() / iter;
			total_U6 = total_U6 + it1->second.getU6() / iter;
			total_U7 = total_U7 + it1->second.getU7() / iter;
			total_Gt = total_Gt + it1->second.getGt() / iter;

			it1->second.setU1(it1->second.getU1() / iter);
			it1->second.setU2(it1->second.getU2() / iter);
			it1->second.setU3(it1->second.getU3() / iter);
			it1->second.setU4(it1->second.getU4() / iter);
			it1->second.setU5(it1->second.getU5() / iter);
			it1->second.setU6(it1->second.getU6() / iter);
			it1->second.setU7(it1->second.getU7() / iter);
			it1->second.setGt(it1->second.getGt() / iter);
			nb_util_cpu++;
		}


		////// Storage of the average utility of each strategy in a CSV file

		std::map<long double, Utilite>::iterator it2;


		std::fstream fout;
		fout.open("Impact of task’s complexity on the average system utility.csv", std::ios::out);
		fout << "Cycles CPU,U1,U2,U3,U4,U5,U6,U7,GT \n";
		for (it2 = utilites_CPU.begin(); it2 != utilites_CPU.end(); it2++)
		{




			fout << std::setprecision(std::numeric_limits< long double>::digits10) << it2->first / 100000 << ", "
				<< it2->second.getU1() << ", "
				<< it2->second.getU2() << ", "
				<< it2->second.getU3() << ", "
				<< it2->second.getU4() << ", "
				<< it2->second.getU5() << ", "
				<< it2->second.getU6() << ", "
				<< it2->second.getU7() << ", "
				<< it2->second.getGt() << ", "
				<< "\n";
		}

		/////////Calculation of the average energy of each strategy

		std::map<long double, Energie>::iterator it3;


		long double moy_en_cpu1 = 0;
		long double moy_en_cpu2 = 0;
		long double moy_en_cpu3 = 0;
		long double moy_en_cpu4 = 0;
		long double moy_en_cpu5 = 0;
		long double moy_en_cpu6 = 0;
		long double moy_en_cpu7 = 0;
		long double moy_en_cpugt = 0;
		for (it3 = energies_CPU.begin(); it3 != energies_CPU.end(); it3++)
		{

			moy_en_cpu1 = moy_en_cpu1 + (it3->second.getE1() / iter);
			moy_en_cpu2 = moy_en_cpu2 + (it3->second.getE2() / iter);
			moy_en_cpu3 = moy_en_cpu3 + (it3->second.getE3() / iter);
			moy_en_cpu4 = moy_en_cpu4 + (it3->second.getE4() / iter);
			moy_en_cpu5 = moy_en_cpu5 + (it3->second.getE5() / iter);
			moy_en_cpu6 = moy_en_cpu6 + (it3->second.getE6() / iter);
			moy_en_cpu7 = moy_en_cpu7 + (it3->second.getE7() / iter);
			moy_en_cpugt = moy_en_cpugt + (it3->second.getGt() / iter);
			it3->second.setE1(it3->second.getE1() / iter);
			it3->second.setE2(it3->second.getE2() / iter);
			it3->second.setE3(it3->second.getE3() / iter);
			it3->second.setE4(it3->second.getE4() / iter);
			it3->second.setE5(it3->second.getE5() / iter);
			it3->second.setE6(it3->second.getE6() / iter);
			it3->second.setE7(it3->second.getE7() / iter);
			it3->second.setGt(it3->second.getGt() / iter);

		}
		moy_en_cpu1 = moy_en_cpu1 / energies_CPU.size();
		moy_en_cpu2 = moy_en_cpu2 / energies_CPU.size();
		moy_en_cpu3 = moy_en_cpu3 / energies_CPU.size();
		moy_en_cpu4 = moy_en_cpu4 / energies_CPU.size();
		moy_en_cpu5 = moy_en_cpu5 / energies_CPU.size();
		moy_en_cpu6 = moy_en_cpu6 / energies_CPU.size();
		moy_en_cpu7 = moy_en_cpu7 / energies_CPU.size();
		moy_en_cpugt = moy_en_cpugt / energies_CPU.size();


		/////////Calculation of the average delay for each strategy
		std::map<long double, Temps>::iterator it10;


		long double moy_temps_cpu1 = 0;
		long double moy_temps_cpu2 = 0;
		long double moy_temps_cpu3 = 0;
		long double moy_temps_cpu4 = 0;
		long double moy_temps_cpu5 = 0;
		long double moy_temps_cpu6 = 0;
		long double moy_temps_cpu7 = 0;
		long double moy_temps_cpugt = 0;
		for (it10 = temps_CPU.begin(); it10 != temps_CPU.end(); it10++)
		{

			moy_temps_cpu1 = moy_temps_cpu1 + (it10->second.getT1() / iter);
			moy_temps_cpu2 = moy_temps_cpu2 + (it10->second.getT2() / iter);
			moy_temps_cpu3 = moy_temps_cpu3 + (it10->second.getT3() / iter);
			moy_temps_cpu4 = moy_temps_cpu4 + (it10->second.getT4() / iter);
			moy_temps_cpu5 = moy_temps_cpu5 + (it10->second.getT5() / iter);
			moy_temps_cpu6 = moy_temps_cpu6 + (it10->second.getT6() / iter);
			moy_temps_cpu7 = moy_temps_cpu7 + (it10->second.getT7() / iter);
			moy_temps_cpugt = moy_temps_cpugt + (it10->second.getGt() / iter);
			it10->second.setT1(it10->second.getT1() / iter);
			it10->second.setT2(it10->second.getT2() / iter);
			it10->second.setT3(it10->second.getT3() / iter);
			it10->second.setT4(it10->second.getT4() / iter);
			it10->second.setT5(it10->second.getT5() / iter);
			it10->second.setT6(it10->second.getT6() / iter);
			it10->second.setT7(it10->second.getT7() / iter);
			it10->second.setGt(it10->second.getGt() / iter);

		}
		moy_temps_cpu1 = moy_temps_cpu1 / temps_CPU.size();
		moy_temps_cpu2 = moy_temps_cpu2 / temps_CPU.size();
		moy_temps_cpu3 = moy_temps_cpu3 / temps_CPU.size();
		moy_temps_cpu4 = moy_temps_cpu4 / temps_CPU.size();
		moy_temps_cpu5 = moy_temps_cpu5 / temps_CPU.size();
		moy_temps_cpu6 = moy_temps_cpu6 / temps_CPU.size();
		moy_temps_cpu7 = moy_temps_cpu7 / temps_CPU.size();
		moy_temps_cpugt = moy_temps_cpugt / temps_CPU.size();


		std::map<long double, CoutEnvoie >::iterator it20;


		long double moy_ce_cpu1 = 0;
		long double moy_ce_cpu2 = 0;
		long double moy_ce_cpu3 = 0;
		long double moy_ce_cpu4 = 0;
		long double moy_ce_cpu5 = 0;
		long double moy_ce_cpu6 = 0;
		long double moy_ce_cpu7 = 0;
		long double moy_ce_cpugt = 0;
		for (it20 = coutEnvoi_CPU.begin(); it20 != coutEnvoi_CPU.end(); it20++)
		{

			moy_ce_cpu1 = moy_ce_cpu1 + (it20->second.getCE1() / iter);
			moy_ce_cpu2 = moy_ce_cpu2 + (it20->second.getCE2() / iter);
			moy_ce_cpu3 = moy_ce_cpu3 + (it20->second.getCE3() / iter);
			moy_ce_cpu4 = moy_ce_cpu4 + (it20->second.getCE4() / iter);
			moy_ce_cpu5 = moy_ce_cpu5 + (it20->second.getCE5() / iter);
			moy_ce_cpu6 = moy_ce_cpu6 + (it20->second.getCE6() / iter);
			moy_ce_cpu7 = moy_ce_cpu7 + (it20->second.getCE7() / iter);
			moy_ce_cpugt = moy_ce_cpugt + (it20->second.getGt() / iter);
			it20->second.setCE1(it20->second.getCE1() / iter);
			it20->second.setCE2(it20->second.getCE2() / iter);
			it20->second.setCE3(it20->second.getCE3() / iter);
			it20->second.setCE4(it20->second.getCE4() / iter);
			it20->second.setCE5(it20->second.getCE5() / iter);
			it20->second.setCE6(it20->second.getCE6() / iter);
			it20->second.setCE7(it20->second.getCE7() / iter);
			it20->second.setGt(it20->second.getGt() / iter);

		}
		moy_ce_cpu1 = moy_ce_cpu1 / coutEnvoi_CPU.size();
		moy_ce_cpu2 = moy_ce_cpu2 / coutEnvoi_CPU.size();
		moy_ce_cpu3 = moy_ce_cpu3 / coutEnvoi_CPU.size();
		moy_ce_cpu4 = moy_ce_cpu4 / coutEnvoi_CPU.size();
		moy_ce_cpu5 = moy_ce_cpu5 / coutEnvoi_CPU.size();
		moy_ce_cpu6 = moy_ce_cpu6 / coutEnvoi_CPU.size();
		moy_ce_cpu7 = moy_ce_cpu7 / coutEnvoi_CPU.size();
		moy_ce_cpugt = moy_ce_cpugt / coutEnvoi_CPU.size();



		std::map<long double, CoutCalcul >::iterator it21;


		long double moy_cc_cpu1 = 0;
		long double moy_cc_cpu2 = 0;
		long double moy_cc_cpu3 = 0;
		long double moy_cc_cpu4 = 0;
		long double moy_cc_cpu5 = 0;
		long double moy_cc_cpu6 = 0;
		long double moy_cc_cpu7 = 0;
		long double moy_cc_cpugt = 0;
		for (it21 = coutCalcul_CPU.begin(); it21 != coutCalcul_CPU.end(); it21++)
		{

			moy_cc_cpu1 = moy_cc_cpu1 + (it21->second.getCC1() / iter);
			moy_cc_cpu2 = moy_cc_cpu2 + (it21->second.getCC2() / iter);
			moy_cc_cpu3 = moy_cc_cpu3 + (it21->second.getCC3() / iter);
			moy_cc_cpu4 = moy_cc_cpu4 + (it21->second.getCC4() / iter);
			moy_cc_cpu5 = moy_cc_cpu5 + (it21->second.getCC5() / iter);
			moy_cc_cpu6 = moy_cc_cpu6 + (it21->second.getCC6() / iter);
			moy_cc_cpu7 = moy_cc_cpu7 + (it21->second.getCC7() / iter);
			moy_cc_cpugt = moy_cc_cpugt + (it21->second.getGt() / iter);
			it21->second.setCC1(it21->second.getCC1() / iter);
			it21->second.setCC2(it21->second.getCC2() / iter);
			it21->second.setCC3(it21->second.getCC3() / iter);
			it21->second.setCC4(it21->second.getCC4() / iter);
			it21->second.setCC5(it21->second.getCC5() / iter);
			it21->second.setCC6(it21->second.getCC6() / iter);
			it21->second.setCC7(it21->second.getCC7() / iter);
			it21->second.setGt(it21->second.getGt() / iter);

		}
		moy_cc_cpu1 = moy_cc_cpu1 / coutCalcul_CPU.size();
		moy_cc_cpu2 = moy_cc_cpu2 / coutCalcul_CPU.size();
		moy_cc_cpu3 = moy_cc_cpu3 / coutCalcul_CPU.size();
		moy_cc_cpu4 = moy_cc_cpu4 / coutCalcul_CPU.size();
		moy_cc_cpu5 = moy_cc_cpu5 / coutCalcul_CPU.size();
		moy_cc_cpu6 = moy_cc_cpu6 / coutCalcul_CPU.size();
		moy_cc_cpu7 = moy_cc_cpu7 / coutCalcul_CPU.size();
		moy_cc_cpugt = moy_cc_cpugt / coutCalcul_CPU.size();

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//SIMULATION n°2  =  Calculation of the overall utility, energy, and timeframe for each strategy in relation to the change in Task Data Size
    
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		cycle_cpu = cycle_cpu_var;
		max_cycle_cpu = max_cycle_cpu_var;
		taille_resultat = taille_resultat_var;
		tailleDonnee = tailleDonnee_var;
		maxTaille = maxTaille_var;

		iter = 1;
		// matrix to store the usefulness of each strategy+GT according to the change in data size [Data_Size, [U1,U2,U3,U4,U5,U6,U7,GT]] 
		std::map<long double, Utilite> utilites_Donnees;
		// matrix to store the energy of each strategy+GT according to the change in data size [Data_Size, [U1,U2,U3,U4,U5,U6,U7,GT]]
		std::map<long double, Energie> energie_Donnees;
		// matrix to store the delay of each strategy+GT according to the change in data size [Data_Size, [U1,U2,U3,U4,U5,U6,U7,GT]]
		std::map<long double, Temps> temps_Donnees;
		// matrix to store the cost of communication for each strategy+GT according to the change in data size [Data_Size, [U1,U2,U3,U4,U5,U6,U7,GT]]
		std::map<long double, CoutEnvoie> coutEnvoi_Donnees;
		// matrix to store the computation cost of each strategy+GT according to the change in data size [Data_Size, [U1,U2,U3,U4,U5,U6,U7,GT]]
		std::map<long double, CoutCalcul> coutCalcul_Donnees;
		while (cycle_cpu <= max_cycle_cpu)
		{
			int i = 0;
			taches.clear();
			while (tailleDonnee <= maxTaille)
			{
				Tache tachei(i, cycle_cpu, tailleDonnee, taille_resultat, 1);
				taches.push_back(tachei);
				tailleDonnee = tailleDonnee * 2;
				i++;

			}



			std::multimap < int, Tache> ::iterator itr;
			int meilleurStrategie;
			long double meilleurUtilite;
			long double meilleurEnergie;
			long double meilleurTemps;
			long double meilleurCoutEnvoi;
			long double meilleurCoutCalcul;
			long double temp_util = 0;
			long double temp_energ = 0;
			long double temp_temps = 0;
			long double temp_ce = 0;
			long double temp_cc = 0;
			for (int c = 0; c < taches.size(); c++)
			{
				Utilite temp_util_obj;
				Energie temp_energ_obj;
				Temps temp_temps_obj;
				CoutEnvoie temp_ce_obj;
				CoutCalcul temp_cc_obj;
				Tache ti = taches[c];
				meilleurStrategie = 1;
				meilleurUtilite = 0;
				meilleurEnergie = 0;
				meilleurTemps = 0;
				meilleurCoutEnvoi = 0;
				meilleurCoutCalcul = 0;
				//////////////////////////////////////////////// S1 : local computation /////////////////////////////////////////////
				temp_util = calcul_local_DP(ti, drone_pricipal);
				temp_energ = getEnergieS1(ti, drone_pricipal);
				temp_temps = getTempsS1(ti, drone_pricipal);
				temp_ce = getCES1(ti);
				temp_cc = getCCS1(ti);
				if (iter == 1) {
					temp_util_obj.setU1(temp_util);
					temp_energ_obj.setE1(temp_energ);
					temp_temps_obj.setT1(temp_temps);
					temp_ce_obj.setCE1(temp_ce);
					temp_cc_obj.setCC1(temp_cc);
				}
				else {

					utilites_Donnees[ti.getDi()].setU1(utilites_Donnees[ti.getDi()].getU1() + temp_util);
					energie_Donnees[ti.getDi()].setE1(energie_Donnees[ti.getDi()].getE1() + temp_energ);
					temps_Donnees[ti.getDi()].setT1(temps_Donnees[ti.getDi()].getT1() + temp_temps);
					coutEnvoi_Donnees[ti.getDi()].setCE1(coutEnvoi_Donnees[ti.getDi()].getCE1() + temp_ce);
					coutCalcul_Donnees[ti.getDi()].setCC1(coutCalcul_Donnees[ti.getDi()].getCC1() + temp_cc);
				}

				utilites_Local.insert(std::pair<int, long double>(ti.getId(), temp_util));
				meilleurUtilite = temp_util;
				meilleurEnergie = temp_energ;
				meilleurTemps = temp_temps;
				meilleurCoutEnvoi = temp_ce;
				meilleurCoutCalcul = temp_cc;

				/////////////////////////////////////////////// S2 : offloading to Edge server/////////////////////////////////
				temp_util = calcul_delestage_SE(ti, serveur_edge);
				temp_energ = getEnergieS2(ti);
				temp_temps = getTempsS2(ti, serveur_edge);
				temp_ce = getCES2(ti);
				temp_cc = getCCS2(ti);
				if (iter == 1) {
					temp_util_obj.setU2(temp_util);
					temp_energ_obj.setE2(temp_energ);
					temp_temps_obj.setT2(temp_temps);
					temp_ce_obj.setCE2(temp_ce);
					temp_cc_obj.setCC2(temp_cc);
				}
				else {

					utilites_Donnees[ti.getDi()].setU2(utilites_Donnees[ti.getDi()].getU2() + temp_util);
					energie_Donnees[ti.getDi()].setE2(energie_Donnees[ti.getDi()].getE2() + temp_energ);
					temps_Donnees[ti.getDi()].setT2(temps_Donnees[ti.getDi()].getT2() + temp_temps);
					coutEnvoi_Donnees[ti.getDi()].setCE2(coutEnvoi_Donnees[ti.getDi()].getCE2() + temp_ce);
					coutCalcul_Donnees[ti.getDi()].setCC2(coutCalcul_Donnees[ti.getDi()].getCC2() + temp_cc);
				}

				utilites_Delestage_SE.insert(std::pair<int, long double>(ti.getId(), temp_util));

				if (temp_util < meilleurUtilite) {
					meilleurStrategie = 2;
					meilleurUtilite = temp_util;
					meilleurEnergie = temp_energ;
					meilleurTemps = temp_temps;
					meilleurCoutEnvoi = temp_ce;
					meilleurCoutCalcul = temp_cc;
				}

				///////////////////////////////////////////////////// S3 :sharing with secondary drones/////////////////////////////////////////////////////////////
				temp_util = calcul_partage_DS(ti, drone_pricipal, drones_secondaires);
				temp_energ = getEnergieS3(ti, drone_pricipal, drones_secondaires);
				temp_temps = getTempsS3(ti, drone_pricipal, drones_secondaires);
				temp_ce = getCES3(ti);
				temp_cc = getCCS3(ti);
				if (iter == 1) {
					temp_util_obj.setU3(temp_util);
					temp_energ_obj.setE3(temp_energ);
					temp_temps_obj.setT3(temp_temps);
					temp_ce_obj.setCE3(temp_ce);
					temp_cc_obj.setCC3(temp_cc);
				}
				else {

					utilites_Donnees[ti.getDi()].setU3(utilites_Donnees[ti.getDi()].getU3() + temp_util);
					energie_Donnees[ti.getDi()].setE3(energie_Donnees[ti.getDi()].getE3() + temp_energ);
					temps_Donnees[ti.getDi()].setT3(temps_Donnees[ti.getDi()].getT3() + temp_temps);
					coutEnvoi_Donnees[ti.getDi()].setCE3(coutEnvoi_Donnees[ti.getDi()].getCE3() + temp_ce);
					coutCalcul_Donnees[ti.getDi()].setCC3(coutCalcul_Donnees[ti.getDi()].getCC3() + temp_cc);
				}

				utilites_Partage_DS.insert(std::pair<int, long double>(ti.getId(), temp_util));
				if (temp_util < meilleurUtilite) {
					meilleurStrategie = 3;
					meilleurUtilite = temp_util;
					meilleurEnergie = temp_energ;
					meilleurTemps = temp_temps;
					meilleurCoutEnvoi = temp_ce;
					meilleurCoutCalcul = temp_cc;
				}


				///////////////////////////////////////////////////// S4 : offloading to authority  vehicle + local computation in authority vehicle///////////////////////////////////
				temp_util = calcul_local_VP(ti, vehicule_police);
				temp_energ = getEnergieS4(ti, vehicule_police);
				temp_temps = getTempsS4(ti, vehicule_police);
				temp_ce = getCES4(ti);
				temp_cc = getCCS4(ti);
				if (iter == 1) {
					temp_util_obj.setU4(temp_util);
					temp_energ_obj.setE4(temp_energ);
					temp_temps_obj.setT4(temp_temps);
					temp_ce_obj.setCE4(temp_ce);
					temp_cc_obj.setCC4(temp_cc);
				}
				else {

					utilites_Donnees[ti.getDi()].setU4(utilites_Donnees[ti.getDi()].getU4() + temp_util);
					energie_Donnees[ti.getDi()].setE4(energie_Donnees[ti.getDi()].getE4() + temp_energ);
					temps_Donnees[ti.getDi()].setT4(temps_Donnees[ti.getDi()].getT4() + temp_temps);
					coutEnvoi_Donnees[ti.getDi()].setCE4(coutEnvoi_Donnees[ti.getDi()].getCE4() + temp_ce);
					coutCalcul_Donnees[ti.getDi()].setCC4(coutCalcul_Donnees[ti.getDi()].getCC4() + temp_cc);
				}

				utilites_Local_VP.insert(std::pair<int, long double>(ti.getId(), temp_util));
				if (temp_util < meilleurUtilite) {
					meilleurStrategie = 4;
					meilleurUtilite = temp_util;
					meilleurEnergie = temp_energ;
					meilleurTemps = temp_temps;
					meilleurCoutEnvoi = temp_ce;
					meilleurCoutCalcul = temp_cc;
				}
				/////////////////////////////////////////////////// S5 : offloading to authority vehicle + offloading to Edge server by the authority vehicle///////////////////////////////////////
				temp_util = calcul_delestage_VP_SE(ti, serveur_edge);
				temp_energ = getEnergieS5(ti);
				temp_temps = getTempsS5(ti, serveur_edge);
				temp_ce = getCES5(ti);
				temp_cc = getCCS5(ti);
				if (iter == 1) {
					temp_util_obj.setU5(temp_util);
					temp_energ_obj.setE5(temp_energ);
					temp_temps_obj.setT5(temp_temps);
					temp_ce_obj.setCE5(temp_ce);
					temp_cc_obj.setCC5(temp_cc);
				}
				else {

					utilites_Donnees[ti.getDi()].setU5(utilites_Donnees[ti.getDi()].getU5() + temp_util);
					energie_Donnees[ti.getDi()].setE5(energie_Donnees[ti.getDi()].getE5() + temp_energ);
					temps_Donnees[ti.getDi()].setT5(temps_Donnees[ti.getDi()].getT5() + temp_temps);
					coutEnvoi_Donnees[ti.getDi()].setCE5(coutEnvoi_Donnees[ti.getDi()].getCE5() + temp_ce);
					coutCalcul_Donnees[ti.getDi()].setCC5(coutCalcul_Donnees[ti.getDi()].getCC5() + temp_cc);
				}

				utilites_VP_Delestage_SE.insert(std::pair<int, long double>(ti.getId(), temp_util));
				if (temp_util < meilleurUtilite) {
					meilleurStrategie = 5;
					meilleurUtilite = temp_util;
					meilleurEnergie = temp_energ;
					meilleurTemps = temp_temps;
					meilleurCoutEnvoi = temp_ce;
					meilleurCoutCalcul = temp_cc;
				}


				///////////////////////////////////////////// S6 :  offloading to authority vehicle + sharing with nearby vehicle + accpet computation by nearby vehicle///////////////////////////////////
				temp_util = calcul_partage_VV_accpt(ti, vehicule_police, vehicule_voisin);
				temp_energ = getEnergieS6(ti, vehicule_police, vehicule_voisin);
				temp_temps = getTempsS6(ti, vehicule_voisin);
				temp_ce = getCES6(ti);
				temp_cc = getCCS6(ti);
				if (iter == 1) {
					temp_util_obj.setU6(temp_util);
					temp_energ_obj.setE6(temp_energ);
					temp_temps_obj.setT6(temp_temps);
					temp_ce_obj.setCE6(temp_ce);
					temp_cc_obj.setCC6(temp_cc);
				}
				else {

					utilites_Donnees[ti.getDi()].setU6(utilites_Donnees[ti.getDi()].getU6() + temp_util);
					energie_Donnees[ti.getDi()].setE6(energie_Donnees[ti.getDi()].getE6() + temp_energ);
					temps_Donnees[ti.getDi()].setT6(temps_Donnees[ti.getDi()].getT6() + temp_temps);
					coutEnvoi_Donnees[ti.getDi()].setCE6(coutEnvoi_Donnees[ti.getDi()].getCE6() + temp_ce);
					coutCalcul_Donnees[ti.getDi()].setCC6(coutCalcul_Donnees[ti.getDi()].getCC6() + temp_cc);
				}

				utilites_VP_Partage_VV_accpt.insert(std::pair<int, long double>(ti.getId(), temp_util));
				if (temp_util < meilleurUtilite) {
					meilleurStrategie = 6;
					meilleurUtilite = temp_util;
					meilleurEnergie = temp_energ;
					meilleurTemps = temp_temps;
					meilleurCoutEnvoi = temp_ce;
					meilleurCoutCalcul = temp_cc;
				}
				/////////////////////////////////////// S7 : offloading to authority vehicle + sharing with nearby vehicle + refuse computation by nearby vehicle/////////////////////////////////////
				temp_util = calcul_partage_VV_refu(ti, vehicule_police);
				temp_energ = getEnergieS7(ti, vehicule_police);
				temp_temps = getTempsS7(ti, vehicule_police);
				temp_ce = getCES7(ti);
				temp_cc = getCCS7(ti);
				if (iter == 1) {
					temp_util_obj.setU7(temp_util);
					temp_energ_obj.setE7(temp_energ);
					temp_temps_obj.setT7(temp_temps);
					temp_ce_obj.setCE7(temp_ce);
					temp_cc_obj.setCC7(temp_cc);
				}
				else {

					utilites_Donnees[ti.getDi()].setU7(utilites_Donnees[ti.getDi()].getU7() + temp_util);
					energie_Donnees[ti.getDi()].setE7(energie_Donnees[ti.getDi()].getE7() + temp_energ);
					temps_Donnees[ti.getDi()].setT7(temps_Donnees[ti.getDi()].getT7() + temp_temps);
					coutEnvoi_Donnees[ti.getDi()].setCE7(coutEnvoi_Donnees[ti.getDi()].getCE7() + temp_ce);
					coutCalcul_Donnees[ti.getDi()].setCC7(coutCalcul_Donnees[ti.getDi()].getCC7() + temp_cc);
				}

				utilites_VP_Partage_VV_refu.insert(std::pair<int, long double>(ti.getId(), temp_util));
				if (temp_util < meilleurUtilite) {
					meilleurStrategie = 7;
					meilleurUtilite = temp_util;
					meilleurEnergie = temp_energ;
					meilleurTemps = temp_temps;
					meilleurCoutEnvoi = temp_ce;
					meilleurCoutCalcul = temp_cc;
				}

				if (iter == 1) {
					temp_util_obj.setGt(meilleurUtilite);
					temp_energ_obj.setGt(meilleurEnergie);
					temp_temps_obj.setGt(meilleurTemps);
					temp_ce_obj.setGt(meilleurCoutEnvoi);
					temp_cc_obj.setGt(meilleurCoutCalcul);
				}
				else {

					utilites_Donnees[ti.getDi()].setGt(utilites_Donnees[ti.getDi()].getGt() + meilleurUtilite);
					energie_Donnees[ti.getDi()].setGt(energie_Donnees[ti.getDi()].getGt() + meilleurEnergie);
					temps_Donnees[ti.getDi()].setGt(temps_Donnees[ti.getDi()].getGt() + meilleurTemps);
					coutEnvoi_Donnees[ti.getDi()].setGt(coutEnvoi_Donnees[ti.getDi()].getGt() + meilleurCoutEnvoi);
					coutCalcul_Donnees[ti.getDi()].setGt(coutCalcul_Donnees[ti.getDi()].getGt() + meilleurCoutCalcul);
				}

				if (iter == 1) {
					utilites_Donnees.insert(std::pair<long double, Utilite>(ti.getDi(), temp_util_obj));
					energie_Donnees.insert(std::pair<long double, Energie>(ti.getDi(), temp_energ_obj));
					temps_Donnees.insert(std::pair<long double, Temps>(ti.getDi(), temp_temps_obj));
					coutEnvoi_Donnees.insert(std::pair<long double, CoutEnvoie>(ti.getDi(), temp_ce_obj));
					coutCalcul_Donnees.insert(std::pair<long double, CoutCalcul>(ti.getDi(), temp_cc_obj));
				}


				std::cout << "Tache num " << ti.getId() << " Ci: " << ti.getCi() << " Di: " << ti.getDi() << " U1  " << utilites_Donnees[ti.getDi()].getU1() << " U2 " << utilites_Donnees[ti.getDi()].getU2() << " U3 " << utilites_Donnees[ti.getDi()].getU3() << " U4 " << utilites_Donnees[ti.getDi()].getU4() << " U5 " << utilites_Donnees[ti.getDi()].getU5() << " U6 " << utilites_Donnees[ti.getDi()].getU6() << "U7 " << utilites_Donnees[ti.getDi()].getU7() << "Meuilleur S" << meilleurStrategie << '\n';

			}


			iter++;




			cycle_cpu = cycle_cpu * 2;
			tailleDonnee = tailleDonnee_var;
		}
		iter--;

		/////////Calculation of the average utility of each strategy

		std::map<long double, Utilite>::iterator it5;


		int nb_util_donnes = 0;
		for (it5 = utilites_Donnees.begin(); it5 != utilites_Donnees.end(); it5++)
		{
			total_U1 = total_U1 + it5->second.getU1() / iter;
			total_U2 = total_U2 + it5->second.getU2() / iter;
			total_U3 = total_U3 + it5->second.getU3() / iter;
			total_U4 = total_U4 + it5->second.getU4() / iter;
			total_U5 = total_U5 + it5->second.getU5() / iter;
			total_U6 = total_U6 + it5->second.getU6() / iter;
			total_U7 = total_U7 + it5->second.getU7() / iter;
			total_Gt = total_Gt + it5->second.getGt() / iter;
			it5->second.setU1(it5->second.getU1() / iter);
			it5->second.setU2(it5->second.getU2() / iter);
			it5->second.setU3(it5->second.getU3() / iter);
			it5->second.setU4(it5->second.getU4() / iter);
			it5->second.setU5(it5->second.getU5() / iter);
			it5->second.setU6(it5->second.getU6() / iter);
			it5->second.setU7(it5->second.getU7() / iter);
			it5->second.setGt(it5->second.getGt() / iter);
			nb_util_donnes++;
		}


		std::map<long double, Utilite>::iterator it6;


		std::fstream fout3;
		fout3.open("Impact of different data sizes on the average system utility.csv", std::ios::out);
		fout3 << "Taille Données (Ko),U1,U2,U3,U4,U5,U6,U7,GT \n";
		for (it6 = utilites_Donnees.begin(); it6 != utilites_Donnees.end(); it6++)
		{




			fout3 << std::setprecision(std::numeric_limits< long double>::digits10) << it6->first / 100 << ", "
				<< it6->second.getU1() << ", "
				<< it6->second.getU2() << ", "
				<< it6->second.getU3() << ", "
				<< it6->second.getU4() << ", "
				<< it6->second.getU5() << ", "
				<< it6->second.getU6() << ", "
				<< it6->second.getU7() << ", "
				<< it6->second.getGt() << ", "
				<< "\n";

		}

		/////////Calculation of the average energy of each strategy

		std::map<long double, Energie>::iterator it23;

		std::fstream fout23;
		fout23.open("Impact of different data sizes on the average system energy.csv", std::ios::out);
		fout23 << "Taille Données (Ko),E1,E2,E3,E4,E5,E6,E7,GT \n";
		for (it23 = energie_Donnees.begin(); it23 != energie_Donnees.end(); it23++)
		{




			fout23 << std::setprecision(std::numeric_limits< long double>::digits10) << it23->first / 100 << ", "
				<< it23->second.getE1() / iter << ", "
				<< it23->second.getE2() / iter << ", "
				<< it23->second.getE3() / iter << ", "
				<< it23->second.getE4() / iter << ", "
				<< it23->second.getE5() / iter << ", "
				<< it23->second.getE6() / iter << ", "
				<< it23->second.getE7() / iter << ", "
				<< it23->second.getGt() / iter << ", "
				<< "\n";

		}


		/////////Calculation of the average delay for each strategy

		std::map<long double, Temps>::iterator it24;


		std::fstream fout24;
		fout24.open("Impact of different data sizes on the average system delay.csv", std::ios::out);
		fout24 << "Taille Données (Ko),T1,T2,T3,T4,T5,T6,T7,GT \n";
		for (it24 = temps_Donnees.begin(); it24 != temps_Donnees.end(); it24++)
		{




			fout24 << std::setprecision(std::numeric_limits< long double>::digits10) << it24->first / 1000 << ", "
				<< it24->second.getT1() / iter << ", "
				<< it24->second.getT2() / iter << ", "
				<< it24->second.getT3() / iter << ", "
				<< it24->second.getT4() / iter << ", "
				<< it24->second.getT5() / iter << ", "
				<< it24->second.getT6() / iter << ", "
				<< it24->second.getT7() / iter << ", "
				<< it24->second.getGt() / iter << ", "
				<< "\n";

		}

		std::map<long double, Energie>::iterator it7;


		long double moy_en_data1 = 0;
		long double moy_en_data2 = 0;
		long double moy_en_data3 = 0;
		long double moy_en_data4 = 0;
		long double moy_en_data5 = 0;
		long double moy_en_data6 = 0;
		long double moy_en_data7 = 0;
		long double moy_en_datagt = 0;

		for (it7 = energie_Donnees.begin(); it7 != energie_Donnees.end(); it7++)
		{
			moy_en_data1 = moy_en_data1 + (it7->second.getE1() / iter);
			moy_en_data2 = moy_en_data2 + (it7->second.getE2() / iter);
			moy_en_data3 = moy_en_data3 + (it7->second.getE3() / iter);
			moy_en_data4 = moy_en_data4 + (it7->second.getE4() / iter);
			moy_en_data5 = moy_en_data5 + (it7->second.getE5() / iter);
			moy_en_data6 = moy_en_data6 + (it7->second.getE6() / iter);
			moy_en_data7 = moy_en_data7 + (it7->second.getE7() / iter);
			moy_en_datagt = moy_en_datagt + (it7->second.getGt() / iter);
			it7->second.setE1(it7->second.getE1() / iter);
			it7->second.setE2(it7->second.getE2() / iter);
			it7->second.setE3(it7->second.getE3() / iter);
			it7->second.setE4(it7->second.getE4() / iter);
			it7->second.setE5(it7->second.getE5() / iter);
			it7->second.setE6(it7->second.getE6() / iter);
			it7->second.setE7(it7->second.getE7() / iter);
			it7->second.setGt(it7->second.getGt() / iter);

		}

		moy_en_data1 = moy_en_data1 / energie_Donnees.size();
		moy_en_data2 = moy_en_data2 / energie_Donnees.size();
		moy_en_data3 = moy_en_data3 / energie_Donnees.size();
		moy_en_data4 = moy_en_data4 / energie_Donnees.size();
		moy_en_data5 = moy_en_data5 / energie_Donnees.size();
		moy_en_data6 = moy_en_data6 / energie_Donnees.size();
		moy_en_data7 = moy_en_data7 / energie_Donnees.size();
		moy_en_datagt = moy_en_datagt / energie_Donnees.size();

		long double moy_en_total1 = (moy_en_data1 + moy_en_cpu1) / 2;
		long double moy_en_total2 = (moy_en_data2 + moy_en_cpu2) / 2;
		long double moy_en_total3 = (moy_en_data3 + moy_en_cpu3) / 2;
		long double moy_en_total4 = (moy_en_data4 + moy_en_cpu4) / 2;
		long double moy_en_total5 = (moy_en_data5 + moy_en_cpu5) / 2;
		long double moy_en_total6 = (moy_en_data6 + moy_en_cpu6) / 2;
		long double moy_en_total7 = (moy_en_data7 + moy_en_cpu7) / 2;
		long double moy_en_totalgt = (moy_en_datagt + moy_en_cpugt) / 2;




		std::map<long double, Temps>::iterator it11;


		long double moy_temps_data1 = 0;
		long double moy_temps_data2 = 0;
		long double moy_temps_data3 = 0;
		long double moy_temps_data4 = 0;
		long double moy_temps_data5 = 0;
		long double moy_temps_data6 = 0;
		long double moy_temps_data7 = 0;
		long double moy_temps_datagt = 0;

		for (it11 = temps_Donnees.begin(); it11 != temps_Donnees.end(); it11++)
		{
			moy_temps_data1 = moy_temps_data1 + (it11->second.getT1() / iter);
			moy_temps_data2 = moy_temps_data2 + (it11->second.getT2() / iter);
			moy_temps_data3 = moy_temps_data3 + (it11->second.getT3() / iter);
			moy_temps_data4 = moy_temps_data4 + (it11->second.getT4() / iter);
			moy_temps_data5 = moy_temps_data5 + (it11->second.getT5() / iter);
			moy_temps_data6 = moy_temps_data6 + (it11->second.getT6() / iter);
			moy_temps_data7 = moy_temps_data7 + (it11->second.getT7() / iter);
			moy_temps_datagt = moy_temps_datagt + (it11->second.getGt() / iter);
			it11->second.setT1(it11->second.getT1() / iter);
			it11->second.setT2(it11->second.getT2() / iter);
			it11->second.setT3(it11->second.getT3() / iter);
			it11->second.setT4(it11->second.getT4() / iter);
			it11->second.setT5(it11->second.getT5() / iter);
			it11->second.setT6(it11->second.getT6() / iter);
			it11->second.setT7(it11->second.getT7() / iter);
			it11->second.setGt(it11->second.getGt() / iter);

		}

		moy_temps_data1 = moy_temps_data1 / temps_Donnees.size();
		moy_temps_data2 = moy_temps_data2 / temps_Donnees.size();
		moy_temps_data3 = moy_temps_data3 / temps_Donnees.size();
		moy_temps_data4 = moy_temps_data4 / temps_Donnees.size();
		moy_temps_data5 = moy_temps_data5 / temps_Donnees.size();
		moy_temps_data6 = moy_temps_data6 / temps_Donnees.size();
		moy_temps_data7 = moy_temps_data7 / temps_Donnees.size();
		moy_temps_datagt = moy_temps_datagt / temps_Donnees.size();

		long double moy_cpu_total1 = (moy_temps_data1 + moy_temps_cpu1) / 2;
		long double moy_cpu_total2 = (moy_temps_data2 + moy_temps_cpu2) / 2;
		long double moy_cpu_total3 = (moy_temps_data3 + moy_temps_cpu3) / 2;
		long double moy_cpu_total4 = (moy_temps_data4 + moy_temps_cpu4) / 2;
		long double moy_cpu_total5 = (moy_temps_data5 + moy_temps_cpu5) / 2;
		long double moy_cpu_total6 = (moy_temps_data6 + moy_temps_cpu6) / 2;
		long double moy_cpu_total7 = (moy_temps_data7 + moy_temps_cpu7) / 2;
		long double moy_cpu_totalgt = (moy_temps_datagt + moy_temps_cpugt) / 2;



		std::map<long double, CoutEnvoie >::iterator it30;


		long double moy_ce_data1 = 0;
		long double moy_ce_data2 = 0;
		long double moy_ce_data3 = 0;
		long double moy_ce_data4 = 0;
		long double moy_ce_data5 = 0;
		long double moy_ce_data6 = 0;
		long double moy_ce_data7 = 0;
		long double moy_ce_datagt = 0;
		for (it30 = coutEnvoi_Donnees.begin(); it30 != coutEnvoi_Donnees.end(); it30++)
		{

			moy_ce_data1 = moy_ce_data1 + (it30->second.getCE1() / iter);
			moy_ce_data2 = moy_ce_data2 + (it30->second.getCE2() / iter);
			moy_ce_data3 = moy_ce_data3 + (it30->second.getCE3() / iter);
			moy_ce_data4 = moy_ce_data4 + (it30->second.getCE4() / iter);
			moy_ce_data5 = moy_ce_data5 + (it30->second.getCE5() / iter);
			moy_ce_data6 = moy_ce_data6 + (it30->second.getCE6() / iter);
			moy_ce_data7 = moy_ce_data7 + (it30->second.getCE7() / iter);
			moy_ce_datagt = moy_ce_datagt + (it30->second.getGt() / iter);
			it30->second.setCE1(it30->second.getCE1() / iter);
			it30->second.setCE2(it30->second.getCE2() / iter);
			it30->second.setCE3(it30->second.getCE3() / iter);
			it30->second.setCE4(it30->second.getCE4() / iter);
			it30->second.setCE5(it30->second.getCE5() / iter);
			it30->second.setCE6(it30->second.getCE6() / iter);
			it30->second.setCE7(it30->second.getCE7() / iter);
			it30->second.setGt(it30->second.getGt() / iter);

		}
		moy_ce_data1 = moy_ce_data1 / coutEnvoi_Donnees.size();
		moy_ce_data2 = moy_ce_data2 / coutEnvoi_Donnees.size();
		moy_ce_data3 = moy_ce_data3 / coutEnvoi_Donnees.size();
		moy_ce_data4 = moy_ce_data4 / coutEnvoi_Donnees.size();
		moy_ce_data5 = moy_ce_data5 / coutEnvoi_Donnees.size();
		moy_ce_data6 = moy_ce_data6 / coutEnvoi_Donnees.size();
		moy_ce_data7 = moy_ce_data7 / coutEnvoi_Donnees.size();
		moy_ce_datagt = moy_ce_datagt / coutEnvoi_Donnees.size();



		long double moy_ce_total1 = (moy_ce_data1 + moy_ce_cpu1) / 2;
		long double moy_ce_total2 = (moy_ce_data2 + moy_ce_cpu2) / 2;
		long double moy_ce_total3 = (moy_ce_data3 + moy_ce_cpu3) / 2;
		long double moy_ce_total4 = (moy_ce_data4 + moy_ce_cpu4) / 2;
		long double moy_ce_total5 = (moy_ce_data5 + moy_ce_cpu5) / 2;
		long double moy_ce_total6 = (moy_ce_data6 + moy_ce_cpu6) / 2;
		long double moy_ce_total7 = (moy_ce_data7 + moy_ce_cpu7) / 2;
		long double moy_ce_totalgt = (moy_ce_datagt + moy_ce_cpugt) / 2;



		std::map<long double, CoutCalcul >::iterator it31;


		long double moy_cc_data1 = 0;
		long double moy_cc_data2 = 0;
		long double moy_cc_data3 = 0;
		long double moy_cc_data4 = 0;
		long double moy_cc_data5 = 0;
		long double moy_cc_data6 = 0;
		long double moy_cc_data7 = 0;
		long double moy_cc_datagt = 0;
		for (it31 = coutCalcul_Donnees.begin(); it31 != coutCalcul_Donnees.end(); it31++)
		{

			moy_cc_data1 = moy_cc_data1 + (it31->second.getCC1() / iter);
			moy_cc_data2 = moy_cc_data2 + (it31->second.getCC2() / iter);
			moy_cc_data3 = moy_cc_data3 + (it31->second.getCC3() / iter);
			moy_cc_data4 = moy_cc_data4 + (it31->second.getCC4() / iter);
			moy_cc_data5 = moy_cc_data5 + (it31->second.getCC5() / iter);
			moy_cc_data6 = moy_cc_data6 + (it31->second.getCC6() / iter);
			moy_cc_data7 = moy_cc_data7 + (it31->second.getCC7() / iter);
			moy_cc_datagt = moy_cc_datagt + (it31->second.getGt() / iter);
			it31->second.setCC1(it31->second.getCC1() / iter);
			it31->second.setCC2(it31->second.getCC2() / iter);
			it31->second.setCC3(it31->second.getCC3() / iter);
			it31->second.setCC4(it31->second.getCC4() / iter);
			it31->second.setCC5(it31->second.getCC5() / iter);
			it31->second.setCC6(it31->second.getCC6() / iter);
			it31->second.setCC7(it31->second.getCC7() / iter);
			it31->second.setGt(it31->second.getGt() / iter);

		}
		moy_cc_data1 = moy_cc_data1 / coutEnvoi_Donnees.size();
		moy_cc_data2 = moy_cc_data2 / coutEnvoi_Donnees.size();
		moy_cc_data3 = moy_cc_data3 / coutEnvoi_Donnees.size();
		moy_cc_data4 = moy_cc_data4 / coutEnvoi_Donnees.size();
		moy_cc_data5 = moy_cc_data5 / coutEnvoi_Donnees.size();
		moy_cc_data6 = moy_cc_data6 / coutEnvoi_Donnees.size();
		moy_cc_data7 = moy_cc_data7 / coutEnvoi_Donnees.size();
		moy_cc_datagt = moy_cc_datagt / coutEnvoi_Donnees.size();



		long double moy_cc_total1 = (moy_cc_data1 + moy_cc_cpu1) / 2;
		long double moy_cc_total2 = (moy_cc_data2 + moy_cc_cpu2) / 2;
		long double moy_cc_total3 = (moy_cc_data3 + moy_cc_cpu3) / 2;
		long double moy_cc_total4 = (moy_cc_data4 + moy_cc_cpu4) / 2;
		long double moy_cc_total5 = (moy_cc_data5 + moy_cc_cpu5) / 2;
		long double moy_cc_total6 = (moy_cc_data6 + moy_cc_cpu6) / 2;
		long double moy_cc_total7 = (moy_cc_data7 + moy_cc_cpu7) / 2;
		long double moy_cc_totalgt = (moy_cc_datagt + moy_cc_cpugt) / 2;




		/////////Storage of the global average energy of each strategy
		std::fstream fout10;
		fout10.open("Average energy of each strategy.csv", std::ios::out);
		fout10 << "Strategie,Moyenne Energie \n";





		fout10 << std::setprecision(std::numeric_limits< long double>::digits10) << "S1" << ", "
			<< moy_en_total1 << "\n"
			<< "S2" << ", "
			<< moy_en_total2 << "\n"
			<< "S3" << ", "
			<< moy_en_total3 << "\n"
			<< "S4" << ", "
			<< moy_en_total4 << "\n"
			<< "S5" << ", "
			<< moy_en_total5 << "\n"
			<< "S6" << ", "
			<< moy_en_total6 << "\n"
			<< "S7" << ", "
			<< moy_en_total7 << "\n"
			<< "GT" << ", "
			<< moy_en_totalgt << "\n";

		std::fstream fout4;

		/////////Storage of the average overall delay for each strategy
		fout4.open("Average delay of each strategy.csv", std::ios::out);
		fout4 << "Strategie,Moyenne Temps \n";





		fout4 << std::setprecision(std::numeric_limits< long double>::digits10) << "S1" << ", "
			<< moy_cpu_total1 << "\n"
			<< "S2" << ", "
			<< moy_cpu_total2 << "\n"
			<< "S3" << ", "
			<< moy_cpu_total3 << "\n"
			<< "S4" << ", "
			<< moy_cpu_total4 << "\n"
			<< "S5" << ", "
			<< moy_cpu_total5 << "\n"
			<< "S6" << ", "
			<< moy_cpu_total6 << "\n"
			<< "S7" << ", "
			<< moy_cpu_total7 << "\n"
			<< "GT" << ", "
			<< moy_cpu_totalgt << "\n";


		

	
		//Calculation of the overall utility of the system ---> (average CPU_Utility + average Data_Utility_Size)/2

		std::fstream fout5;
		fout5.open("Average System Utility.csv", std::ios::out);
		fout5 << "Strategy,Globale Utility\n";





		fout5 << std::setprecision(std::numeric_limits< long double>::digits10) << "S1" << ", "
			<< total_U1 / (nb_util_cpu + nb_util_donnes) << "\n"
			<< "S2" << ", "
			<< total_U2 / (nb_util_cpu + nb_util_donnes) << "\n"
			<< "S3" << ", "
			<< total_U3 / (nb_util_cpu + nb_util_donnes) << "\n"
			<< "S4" << ", "
			<< total_U4 / (nb_util_cpu + nb_util_donnes) << "\n"
			<< "S5" << ", "
			<< total_U5 / (nb_util_cpu + nb_util_donnes) << "\n"
			<< "S6" << ", "
			<< total_U6 / (nb_util_cpu + nb_util_donnes) << "\n"
			<< "S7" << ", "
			<< total_U7 / (nb_util_cpu + nb_util_donnes) << "\n"
			<< "GT" << ", "
			<< total_Gt / (nb_util_cpu + nb_util_donnes) << "\n";







		     
	         	MessageBox::Show("Results are exported successfully in the project folder ", "Simulation Done", MessageBoxButtons::OK, MessageBoxIcon::Information);



















	}

			 long double getEnergieS1(Tache ti,Drone drone_pricipal) {

				 long double E_resultat = ti.getRsi()*E_PC5;
				 long double E_total = drone_pricipal.ECalculCPU(ti.getCi()) + E_resultat;
				 return (E_total - minE) / (maxE - minE);
			 }
			 long double getEnergieS2(Tache ti) {
				 long double E_envoi_SE = ti.getDi()*E_LTEA;
				 long double E_resultat = ti.getRsi()*E_PC5;
				 long double E_total = E_envoi_SE + E_resultat;
				 return (E_total - minE) / (maxE - minE);
			 }
			 long double getEnergieS3(Tache ti, Drone drone_pricipal, std::vector <Drone> drones_secondaires) {
				 long double nb_drones = drones_secondaires.size() + 1;
				 std::vector<long double> taux_de_partage;

				 taux_de_partage.push_back(0.4);
				 taux_de_partage.push_back(0.4);
				 long double taux_total = 0;

				 for (int i = 0; i < taux_de_partage.size(); i++)
				 {
					 taux_total = taux_total + taux_de_partage[i];
				 }
				 //Energie
				 long double E_local_DP = drone_pricipal.ECalculCPU((1 - taux_total) *ti.getCi());
				 long double E_envoi = taux_total * ti.getDi()*E_PC5;
				 long double E_calcul_DS = 0;
				 for (int i = 0; i < drones_secondaires.size(); i++)
				 {

					 E_calcul_DS = E_calcul_DS + drones_secondaires[i].ECalculCPU(taux_de_partage[i] * ti.getCi());
				 }
				 long double E_resultat_DS = taux_total * ti.getRsi() * E_PC5;
				 long double E_resultat = E_resultat_DS + ti.getRsi() * E_PC5;
				 long double E_total = E_local_DP + E_envoi + E_calcul_DS + E_resultat;
				 return (E_total - minE) / (maxE - minE);
			 }
			 long double getEnergieS4(Tache ti,Vehicule vehicule_police) {

				 long double E_envoi = ti.getDi()*E_PC5;
				 long double E_local_VP = 0;
				 if (vehicule_police.estElectrique()) {

					 E_local_VP = vehicule_police.ECalculCPU(ti.getCi());
				 }
				 long double E_total = E_envoi + E_local_VP;
				 return (E_total - minE) / (maxE - minE);
			 }
			 long double getEnergieS5(Tache ti) {

				 long double E_total = (ti.getDi() * E_PC5) + (ti.getDi() * E_LTEA);
				 return (E_total - minE) / (maxE - minE);
			 }
			 long double getEnergieS6(Tache ti, Vehicule vehicule_police, Vehicule vehicule_voisin) {
				 long double taux_de_partage = 0.5;
				 //Energie
				 long double E_envoi = (ti.getDi()*E_PC5);

				 if (vehicule_police.estElectrique()) {

					 E_envoi = (ti.getDi()*E_PC5) + (taux_de_partage * E_PC5);

				 }
				 long double E_local_VV = 0;
				 long double E_resultat = 0;
				 if (vehicule_voisin.estElectrique()) {

					 E_local_VV = vehicule_voisin.ECalculCPU(taux_de_partage *ti.getCi());
					 E_resultat = taux_de_partage * ti.getRsi();
				 }
				 long double E_total = E_envoi + E_local_VV + E_resultat;
				 return (E_total - minE) / (maxE - minE);
			 }
			 long double getEnergieS7(Tache ti, Vehicule vehicule_police) {

				 long double taux_de_partage = 0.5;
				 long double E_envoi = (ti.getDi()*E_PC5);
				 long double E_local_VP = 0;
				 if (vehicule_police.estElectrique()) {

					 E_envoi = E_envoi + (taux_de_partage*ti.getDi()* E_PC5);
					 E_local_VP = vehicule_police.ECalculCPU(ti.getCi());
				 }
				 long double E_total = E_envoi + E_local_VP;
				 return (E_total - minE) / (maxE - minE);
			 }


			 //////////////////////////////////////// Functions for retrieving the delay for each strategy /////////////////////////////////////////////
			 long double getTempsS1(Tache ti, Drone drone_pricipal) {

				 long double T_resultat = ti.getRsi() / (Debit_PC5 * 1000);
				 long double T_total = drone_pricipal.TCalculCPU(ti.getCi()) + T_resultat;
				 return (T_total - minT) / (maxT - minT);
			 }
			 long double getTempsS2(Tache ti,ServeurEdge serveur_edge) {
				 //Temps
				 long double T_envoi_SE = ti.getDi() / (Debit_LTEA * 1000);
				 long double T_calcul_SE = serveur_edge.TCalculCPU(ti.getCi());
				 long double T_resultat = (ti.getRsi() / (Debit_LTEA * 1000)) + (ti.getRsi() / (Debit_PC5 * 1000));
				 long double T_total = T_envoi_SE + T_calcul_SE + T_resultat;
				 return (T_total - minT) / (maxT - minT);

			 }
			 long double getTempsS3(Tache ti, Drone drone_pricipal, std::vector <Drone> drones_secondaires) {
				 long double nb_drones = drones_secondaires.size() + 1;
				 std::vector<long double> taux_de_partage;

				 taux_de_partage.push_back(0.4);
				 taux_de_partage.push_back(0.4);
				 long double taux_total = 0;

				 for (int i = 0; i < taux_de_partage.size(); i++)
				 {
					 taux_total = taux_total + taux_de_partage[i];
				 }
				 //Temps
				 long double T_local_DP = drone_pricipal.TCalculCPU((1 - taux_total) *ti.getCi());
				 long double T_envoi = (taux_total*ti.getDi()) / (Debit_PC5 * 1000);
				 /*long double T_calcul_DS=0;
				 for (int i = 0; i < drones_secondaires.size(); i++)
				 {
					 long double temp_t = drones_secondaires[i].TCalculCPU(taux_de_partage*ti.getCi());

					 if (temp_t > T_calcul_DS) T_calcul_DS = temp_t;

				 }
				 */
				 long double T_calcul_DS = 0;
				 for (int i = 0; i < drones_secondaires.size(); i++)
				 {
					 T_calcul_DS = T_calcul_DS + drones_secondaires[i].TCalculCPU(taux_de_partage[i] * ti.getCi());
				 }

				 T_calcul_DS = T_calcul_DS / nb_drones;
				 long double T_resultat_DS = (taux_total*ti.getRsi()) / (Debit_PC5 * 1000);
				 long double T_resultat = T_resultat_DS + (ti.getRsi() / (Debit_PC5 * 1000));
				 long double T_total = T_local_DP + T_envoi + T_calcul_DS + T_resultat;
				 return (T_total - minT) / (maxT - minT);
			 }
			 long double getTempsS4(Tache ti,Vehicule vehicule_police) {

				 //Temps
				 long double T_envoi = ti.getDi() / (Debit_PC5 * 1000);
				 long double T_local_VP = vehicule_police.TCalculCPU(ti.getCi());
				 long double T_total = T_envoi + T_local_VP;
				 return (T_total - minT) / (maxT - minT);
			 }
			 long double getTempsS5(Tache ti, ServeurEdge serveur_edge) {

				 //Temps
				 long double T_envoi = (ti.getDi() / (Debit_PC5 * 1000)) + (ti.getDi() / (Debit_LTEA * 1000));
				 long double T_local_SE = serveur_edge.TCalculCPU(ti.getCi());
				 long double T_resultat = ti.getRsi() / (Debit_LTEA * 1000);
				 long double T_total = T_envoi + T_local_SE + T_resultat;
				 return (T_total - minT) / (maxT - minT);
			 }
			 long double getTempsS6(Tache ti, Vehicule vehicule_voisin) {
				 long double taux_de_partage = 0.5;
				 //Temps
				 long double T_envoi = (ti.getDi() / (Debit_PC5 * 1000)) + ((taux_de_partage*ti.getDi()) / (Debit_PC5 * 1000));
				 long double T_local_VV = vehicule_voisin.TCalculCPU(taux_de_partage*ti.getCi());
				 long double T_resultat = (taux_de_partage * ti.getRsi()) / (Debit_PC5 * 1000);
				 long double T_total = T_envoi + T_local_VV + T_resultat;
				 return (T_total - minT) / (maxT - minT);
			 }
			 long double getTempsS7(Tache ti,Vehicule vehicule_police ) {
				 long double taux_de_partage = 0.5;
				 //Temps
				 long double T_envoi = (ti.getDi() / (Debit_PC5 * 1000)) + ((taux_de_partage*ti.getDi()) / (Debit_PC5 * 1000));
				 long double T_local_VP = vehicule_police.TCalculCPU(ti.getCi());
				 long double T_total = T_envoi + T_local_VP;
				 return (T_total - minT) / (maxT - minT);
			 }
			 //////////////////////////////////////// Functions to retrieve the communication cost of each strategy /////////////////////////////////////////////

			 long double getCES1(Tache ti) {
				 return 0;
			 }
			 long double getCES2(Tache ti) {
				 long double C_envoi_SE = (ti.getDi()*C_LTEA);
				 return (C_envoi_SE - minCE) / (maxCE - minCE);

			 }
			 long double getCES3(Tache ti) {
				 return 0;
			 }
			 long double getCES4(Tache ti) {
				 return 0;
			 }
			 long double getCES5(Tache ti) {
				 long double C_envoi_SE = ti.getDi()*C_LTEA;
				 return (C_envoi_SE - minCE) / (maxCE - minCE);
			 }
			 long double getCES6(Tache ti) {
				 return 0;
			 }
			 long double getCES7(Tache ti) {
				 return 0;
			 }

			 //////////////////////////////////////// Functions for retrieving the computation cost of each strategy /////////////////////////////////////////////

			 long double getCCS1(Tache ti) {
				 return 0;
			 }
			 long double getCCS2(Tache ti) {
				 long double C_calcul_SE2 = (ti.getCi()*C_Calcul_SE);
				 return (C_calcul_SE2 - minCC) / (maxCC - minCC);
			 }
			 long double getCCS3(Tache ti) {

				 return 0;
			 }
			 long double getCCS4(Tache ti) {

				 return 0;
			 }
			 long double getCCS5(Tache ti) {
				 long double C_calcul_SE3 = ti.getCi()*C_Calcul_SE;
				 return (C_calcul_SE3 - minCC) / (maxCC - minCC);
			 }
			 long double getCCS6(Tache ti) {
				 long double C_calcul_VV2 = ti.getCi()*C_Calcul_VV;
				 return (C_calcul_VV2 - minCC) / (maxCC - minCC);
			 }
			 long double getCCS7(Tache ti) {
				 return 0;
			 }
			 /////////////////////////////////////////////  Function to calculate the utility of each strategy //////////////////////////////////////////////////////
			 // function to determine the utility of local computation in the main drone 
			 long double calcul_local_DP(Tache ti, Drone drone_pricipal) {
				 //Temps
				 long double T_resultat = ti.getRsi() / (Debit_PC5 * 1000);
				 long double T_total = drone_pricipal.TCalculCPU(ti.getCi()) + T_resultat;

				 //Energie
				 long double E_resultat = ti.getRsi()*E_PC5;
				 long double E_total = drone_pricipal.ECalculCPU(ti.getCi()) + E_resultat;

				 //drone_pricipal.majEnergie(E_total*0.001);
				 if (calculer_limites) {
					 if (T_total > maxT) maxT = T_total;
					 if (T_total < minT) minT = T_total;
					 if (E_total > maxE) maxE = E_total;
					 if (E_total < minE) minE = E_total;
				 }
				 T_total = (T_total - minT) / (maxT - minT);
				 E_total = (E_total - minE) / (maxE - minE);

				 //cout << "T_total: " << T_total << " E_total:" << E_total << " U1: " << ((α*T_total + β * E_total) / δ * (QoL_DP_VP + 1))<<"\n";
				 return ((α*T_total + β * E_total) / (δ * QoL_DP_VP + 1));

			 }
			 // function to calculate the utility of the load shedding of the calculation to the ES
			 long double calcul_delestage_SE(Tache ti,ServeurEdge serveur_edge) {


				 //Temps
				 long double T_envoi_SE = ti.getDi() / (Debit_LTEA * 1000);
				 long double T_calcul_SE = serveur_edge.TCalculCPU(ti.getCi());
				 long double T_resultat = (ti.getRsi() / (Debit_LTEA * 1000)) + (ti.getRsi() / (Debit_PC5 * 1000));
				 long double T_total = T_envoi_SE + T_calcul_SE + T_resultat;

				 //Energie
				 long double E_envoi_SE = ti.getDi()*E_LTEA;
				 long double E_resultat = ti.getRsi()*E_PC5;
				 long double E_total = E_envoi_SE + E_resultat;

				 //Coût envoi/calcul
				 long double C_envoi_SE = (ti.getDi()*C_LTEA);
				 long double C_calcul_SE2 = (ti.getCi()*C_Calcul_SE);
				 std::cout << "---------------------------------------------------------------------- \n";
				 //drone_pricipal.majEnergie(E_total*0.001);
				 //cout << " T envoi au SE " << T_envoi_SE << " T calcul local SE " << T_calcul_SE << " envoi du resulat au VP " << T_resultat << " CoutEn " << C_envoi_SE << " CoutCC " << C_calcul_SE2 << " (λ*C_calcul_SE2) " << (λ*C_calcul_SE2) << "\n";
				 //cout << "C_calcul_SE2 " << C_calcul_SE2 << " maxCC: " << maxCC << " minCC: " << minCC << "\n";
				 if (calculer_limites) {
					 if (T_total > maxT) maxT = T_total;
					 if (T_total < minT) minT = T_total;
					 if (E_total > maxE) maxE = E_total;
					 if (E_total < minE) minE = E_total;
					 if (C_envoi_SE > maxCE) maxCE = C_envoi_SE;
					 if (C_envoi_SE < minCE) minCE = C_envoi_SE;
					 if (C_calcul_SE2 > maxCC) maxCC = C_calcul_SE2;
					 if (C_calcul_SE2 < minCC) minCC = C_calcul_SE2;
				 }

				 //cout <<"C_calcul_SE2 " << C_calcul_SE2 << " maxCC: " << maxCC << " minCC: " << minCC << "\n";
				 T_total = (T_total - minT) / (maxT - minT);
				 E_total = (E_total - minE) / (maxE - minE);
				 if (!envoi_et_calcul_gratuit) {
					 C_envoi_SE = (C_envoi_SE - minCE) / (maxCE - minCE);
					 C_calcul_SE2 = (C_calcul_SE2 - minCC) / (maxCC - minCC);
				 }
				 long double QoL = (QoL_DP_SE + QoL_DP_VP) / 2;

				 //cout << " T envoi au SE " << T_envoi_SE << " T calcul local SE " << T_calcul_SE << " envoi du resulat au VP " << T_resultat << " CoutEn " << C_envoi_SE << " CoutCC " << C_calcul_SE2 << " (λ*C_calcul_SE2) " << (λ*C_calcul_SE2) << "\n";


				 return ((α * T_total + β * E_total) / (δ * QoL + 1)) + (γ*C_envoi_SE) + (λ*C_calcul_SE2);

			 }
			 // function for caclulating the utility of sharing the computation with secondary drones 
			 long double calcul_partage_DS(Tache ti, Drone drone_pricipal, std::vector <Drone> drones_secondaires) {

				 long double nb_drones = drones_secondaires.size() + 1;
				 std::vector<long double> taux_de_partage;

				 taux_de_partage.push_back(0.4);
				 taux_de_partage.push_back(0.4);
				 long double taux_total = 0;

				 for (int i = 0; i < taux_de_partage.size(); i++)
				 {
					 taux_total = taux_total + taux_de_partage[i];
				 }
				 //Temps
				 long double T_local_DP = drone_pricipal.TCalculCPU((1 - taux_total) *ti.getCi());
				 long double T_envoi = (taux_total*ti.getDi()) / (Debit_PC5 * 1000);
				 /*long double T_calcul_DS=0;
				 for (int i = 0; i < drones_secondaires.size(); i++)
				 {
					 long double temp_t = drones_secondaires[i].TCalculCPU(taux_de_partage*ti.getCi());

					 if (temp_t > T_calcul_DS) T_calcul_DS = temp_t;

				 }
				 */
				 long double T_calcul_DS = 0;
				 for (int i = 0; i < drones_secondaires.size(); i++)
				 {
					 T_calcul_DS = T_calcul_DS + drones_secondaires[i].TCalculCPU(taux_de_partage[i] * ti.getCi());
				 }

				 T_calcul_DS = T_calcul_DS / nb_drones;
				 long double T_resultat_DS = (taux_total*ti.getRsi()) / (Debit_PC5 * 1000);
				 long double T_resultat = T_resultat_DS + (ti.getRsi() / (Debit_PC5 * 1000));
				 long double T_total = T_local_DP + T_envoi + T_calcul_DS + T_resultat;


				 //Energie
				 long double E_local_DP = drone_pricipal.ECalculCPU((1 - taux_total) *ti.getCi());
				 long double E_envoi = taux_total * ti.getDi()*E_PC5;
				 long double E_calcul_DS = 0;
				 for (int i = 0; i < drones_secondaires.size(); i++)
				 {

					 E_calcul_DS = E_calcul_DS + drones_secondaires[i].ECalculCPU(taux_de_partage[i] * ti.getCi());
					 //drones_secondaires[i].majEnergie(drones_secondaires[i].ECalculCPU(taux_de_partage*ti.getCi() + taux_de_partage * ti.getRsi()*E_PC5*0.001));
				 }
				 long double E_resultat_DS = taux_total * ti.getRsi() * E_PC5;
				 long double E_resultat = E_resultat_DS + ti.getRsi() * E_PC5;
				 long double E_total = E_local_DP + E_envoi + E_calcul_DS + E_resultat;
				 if (calculer_limites) {
					 if (T_total > maxT) maxT = T_total;
					 if (T_total < minT) minT = T_total;
					 if (E_total > maxE) maxE = E_total;
					 if (E_total < minE) minE = E_total;
				 }
				 T_total = (T_total - minT) / (maxT - minT);
				 E_total = (E_total - minE) / (maxE - minE);

				 long double QoL = (QoL_DP_DS + QoL_DP_VP) / 2;


				 return ((α*T_total + β * E_total) / (δ * QoL + 1));
			 }
			 // function to calculate the utility of offloading the calculation to AV + Local computation in AV  
			 long double calcul_local_VP(Tache ti,Vehicule vehicule_police) {

				 //Temps
				 long double T_envoi = ti.getDi() / (Debit_PC5 * 1000);
				 long double T_local_VP = vehicule_police.TCalculCPU(ti.getCi());
				 long double T_total = T_envoi + T_local_VP;
				 // cout << "T envoi au vp" << T_envoi << "T calcul local VP" << T_local_VP <<"\n";
				  //Energie
				 long double E_envoi = ti.getDi()*E_PC5;
				 long double E_local_VP = 0;
				 if (vehicule_police.estElectrique()) {

					 E_local_VP = vehicule_police.ECalculCPU(ti.getCi());
				 }
				 long double E_total = E_envoi + E_local_VP;
				 if (calculer_limites) {
					 if (T_total > maxT) maxT = T_total;
					 if (T_total < minT) minT = T_total;
					 if (E_total > maxE) maxE = E_total;
					 if (E_total < minE) minE = E_total;
				 }
				 T_total = (T_total - minT) / (maxT - minT);
				 E_total = (E_total - minE) / (maxE - minE);


				 return ((α*T_total + β * E_total) / (δ * QoL_DP_VP + 1));
			 }
			 // function to calculate the usefulness of offloading the calculation to the AV + offloading the calculation to the ES by the AV
			 long double calcul_delestage_VP_SE(Tache ti, ServeurEdge serveur_edge) {

				 //Temps
				 long double T_envoi = (ti.getDi() / (Debit_PC5 * 1000)) + (ti.getDi() / (Debit_LTEA * 1000));
				 long double T_local_SE = serveur_edge.TCalculCPU(ti.getCi());
				 long double T_resultat = ti.getRsi() / (Debit_LTEA * 1000);
				 long double T_total = T_envoi + T_local_SE + T_resultat;
				 //Energie
				 long double E_envoi = (ti.getDi() * E_PC5) + (ti.getDi() * E_LTEA);
				 long double E_total = E_envoi;

				 //Coût envoi/calcul
				 long double C_envoi_SE = ti.getDi()*C_LTEA;
				 long double C_calcul_SE3 = ti.getCi()*C_Calcul_SE;
				 std::cout << "C_calcul_SEVP " << C_calcul_SE3 << " maxCC: " << maxCC << " minCC: " << minCC << "\n";

				 if (calculer_limites) {
					 if (T_total > maxT) maxT = T_total;
					 if (T_total < minT) minT = T_total;
					 if (E_total > maxE) maxE = E_total;
					 if (E_total < minE) minE = E_total;
					 if (C_envoi_SE > maxCE) maxCE = C_envoi_SE;
					 if (C_envoi_SE < minCE) minCE = C_envoi_SE;
					 if (C_calcul_SE3 > maxCC) maxCC = C_calcul_SE3;
					 if (C_calcul_SE3 < minCC) minCC = C_calcul_SE3;
				 }
				 std::cout << "C_calcul_SEVP " << C_calcul_SE3 << " maxCC: " << maxCC << " minCC: " << minCC << "\n";
				 T_total = (T_total - minT) / (maxT - minT);
				 E_total = (E_total - minE) / (maxE - minE);
				 if (!envoi_et_calcul_gratuit) {
					 C_envoi_SE = (C_envoi_SE - minCE) / (maxCE - minCE);
					 C_calcul_SE3 = (C_calcul_SE3 - minCC) / (maxCC - minCC);
				 }
				 long double QoL = (QoL_DP_VP + QoL_VP_SE) / 2;
				 //cout << "T_total: " << T_total << " E_total:" << E_total << "C_envoi_SE: " << C_envoi_SE << " C_calcul_SE:" << C_calcul_SE << " U5: " << ((α * T_total + β * E_total) / (δ * (QoL + 1))) + (γ*C_envoi_SE) + (λ*C_calcul_SE) << "\n";

				 return ((α * T_total + β * E_total) / (δ * QoL + 1)) + (γ*C_envoi_SE) + (λ*C_calcul_SE3);
			 }
			 // function to calculate the utility of offloading the calculation to AV + sharing of the computation with NV + acceptance of the computation by NV
			 long double calcul_partage_VV_accpt(Tache ti,Vehicule vehicule_police,Vehicule vehicule_voisin) {
				 long double taux_de_partage = 0.6;
				 //Temps
				 long double T_envoi = (ti.getDi() / (Debit_PC5 * 1000)) + ((taux_de_partage*ti.getDi()) / (Debit_PC5 * 1000));
				 long double T_local_VV = vehicule_voisin.TCalculCPU(taux_de_partage*ti.getCi());
				 long double T_resultat = (taux_de_partage * ti.getRsi()) / (Debit_PC5 * 1000);
				 long double T_total = T_envoi + T_local_VV + T_resultat;

				 //Energie
				 long double E_envoi = (ti.getDi()*E_PC5);

				 if (vehicule_police.estElectrique()) {

					 E_envoi = (ti.getDi()*E_PC5) + (taux_de_partage * E_PC5);

				 }
				 long double E_local_VV = 0;
				 long double E_resultat = 0;
				 if (vehicule_voisin.estElectrique()) {

					 E_local_VV = vehicule_voisin.ECalculCPU(taux_de_partage *ti.getCi());
					 E_resultat = taux_de_partage * ti.getRsi();
				 }
				 long double E_total = E_envoi + E_local_VV + E_resultat;

				 //Coût calcul
				 long double C_calcul_VV2 = ti.getCi()*C_Calcul_VV;
				 if (calculer_limites) {
					 if (T_total > maxT) maxT = T_total;
					 if (T_total < minT) minT = T_total;
					 if (E_total > maxE) maxE = E_total;
					 if (E_total < minE) minE = E_total;
					 if (C_calcul_VV2 > maxCC) maxCC = C_calcul_VV2;
					 if (C_calcul_VV2 < minCC) minCC = C_calcul_VV2;
				 }
				 T_total = (T_total - minT) / (maxT - minT);
				 E_total = (E_total - minE) / (maxE - minE);
				 if (!envoi_et_calcul_gratuit) {
					 C_calcul_VV2 = (C_calcul_VV2 - minCC) / (maxCC - minCC);
				 }

				 long double QoL = (QoL_DP_VP + QoL_VP_VV) / 2;
				 return ((α * T_total + β * E_total) / (δ * QoL + 1)) + (λ*C_calcul_VV2);
			 }
			 // function to calculate the utility of offloading the calculation to AV + sharing of the computation with NV + refusing of the computation by NV
			 long double calcul_partage_VV_refu(Tache ti,Vehicule vehicule_police) {
				 long double taux_de_partage = 0.5;
				 //Temps
				 long double T_envoi = (ti.getDi() / (Debit_PC5 * 1000)) + ((taux_de_partage*ti.getDi()) / (Debit_PC5 * 1000));
				 long double T_local_VP = vehicule_police.TCalculCPU(ti.getCi());
				 long double T_total = T_envoi + T_local_VP;

				 //Energie
				 long double E_envoi = (ti.getDi()*E_PC5);
				 long double E_local_VP = 0;
				 if (vehicule_police.estElectrique()) {

					 E_envoi = E_envoi + (taux_de_partage*ti.getDi()* E_PC5);
					 E_local_VP = vehicule_police.ECalculCPU(ti.getCi());
				 }
				 long double E_total = E_envoi + E_local_VP;
				 if (calculer_limites) {
					 if (T_total > maxT) maxT = T_total;
					 if (T_total < minT) minT = T_total;
					 if (E_total > maxE) maxE = E_total;
					 if (E_total < minE) minE = E_total;
				 }
				 T_total = (T_total - minT) / (maxT - minT);
				 E_total = (E_total - minE) / (maxE - minE);


				 long double QoL = (QoL_DP_VP + QoL_VP_VV) / 2;
				 return ((α * T_total + β * E_total) / (δ * QoL + 1));
			 }

		
			 void calibrer_limites(Drone drone_pricipal,ServeurEdge serveur_edge, Vehicule vehicule_police, Vehicule vehicule_voisin, std::vector <Drone> drones_secondaires, std::vector <Tache> taches, std::map < int, long double > utilites_Local, std::map < int, long double > utilites_Delestage_SE, std::map < int, long double > utilites_Partage_DS, std::map < int, long double > utilites_Local_VP, std::map < int, long double > utilites_VP_Delestage_SE, std::map < int, long double > utilites_VP_Partage_VV_accpt, std::map < int, long double > utilites_VP_Partage_VV_refu) {
				
				 long double cycle_cpu = cycle_cpu_var;
				 long double max_cycle_cpu = max_cycle_cpu_var;
				 long double taille_resultat = taille_resultat_var;
				 long double tailleDonnee = tailleDonnee_var;
				 long double maxTaille = maxTaille_var;
				 // Loop for initializing the values of the tasks to be calculated as such Ci =[500000,...,10000000], Di=5Mo, Rsi=5ko
				 int iter = 1;

				 std::map<long double, Utilite> utilites_CPU;
				 std::map<long double, Energie> energies_CPU;
				 std::map<long double, Temps> temps_CPU;
				 std::map<long double, CoutEnvoie> coutEnvoi_CPU;
				 std::map<long double, CoutCalcul> coutCalcul_CPU;
				 while (tailleDonnee <= maxTaille)
				 {
					 int i = 0;
					 taches.clear();
					 while (cycle_cpu <= max_cycle_cpu)
					 {
						 Tache tachei(i, cycle_cpu, tailleDonnee, taille_resultat, 1);
						 taches.push_back(tachei);
						 cycle_cpu = cycle_cpu * 2;
						 i++;
					 }



					 std::multimap < int, Tache> ::iterator itr;
					 int meilleurStrategie;// variable used to store the strategy having the best utility for each task
					 long double meilleurUtilite;
					 long double meilleurEnergie;
					 long double meilleurTemps;
					 long double meilleurCoutEnvoi;
					 long double meilleurCoutCalcul;
					 long double temp_util = 0;
					 long double temp_energ = 0;
					 long double temp_temps = 0;
					 long double temp_ce = 0;
					 long double temp_cc = 0;
					 for (int c = 0; c < taches.size(); c++)
					 {
						 Utilite temp_util_obj;
						 Energie temp_ener_obj;
						 Temps temp_temps_obj;
						 CoutEnvoie temp_ce_obj;
						 CoutCalcul temp_cc_obj;
						 Tache ti = taches[c];
						 meilleurStrategie = 1;
						 meilleurUtilite = 0;
						 meilleurEnergie = 0;
						 meilleurTemps = 0;
						 meilleurCoutEnvoi = 0;
						 meilleurCoutCalcul = 0;
						 // S1 : local computation
						 temp_util  = calcul_local_DP(ti,drone_pricipal);
						 temp_energ = getEnergieS1(ti, drone_pricipal);
						 temp_temps = getTempsS1(ti, drone_pricipal);
						 temp_ce = getCES1(ti);
						 temp_cc = getCCS1(ti);
						 if (iter == 1) {
							 temp_util_obj.setU1(temp_util);
							 temp_ener_obj.setE1(temp_energ);
							 temp_temps_obj.setT1(temp_temps);
							 temp_ce_obj.setCE1(temp_ce);
							 temp_cc_obj.setCC1(temp_cc);
						 }
						 else {

							 utilites_CPU[ti.getCi()].setU1(utilites_CPU[ti.getCi()].getU1() + temp_util);
							 energies_CPU[ti.getCi()].setE1(energies_CPU[ti.getCi()].getE1() + temp_energ);
							 temps_CPU[ti.getCi()].setT1(temps_CPU[ti.getCi()].getT1() + temp_temps);
							 coutEnvoi_CPU[ti.getCi()].setCE1(coutEnvoi_CPU[ti.getCi()].getCE1() + temp_ce);
							 coutCalcul_CPU[ti.getCi()].setCC1(coutCalcul_CPU[ti.getCi()].getCC1() + temp_cc);
						 }

						 utilites_Local.insert(std::pair<int, long double>(ti.getId(), temp_util));
						 meilleurUtilite = temp_util;
						 meilleurEnergie = temp_energ;
						 meilleurTemps = temp_temps;
						 meilleurCoutEnvoi = temp_ce;
						 meilleurCoutCalcul = temp_cc;
						 // S2 : offloading to Edge server
						 temp_util  = calcul_delestage_SE(ti, serveur_edge);
						 temp_energ = getEnergieS2(ti);
						 temp_temps = getTempsS2(ti, serveur_edge);
						 temp_ce = getCES2(ti);
						 temp_cc = getCCS2(ti);
						 if (iter == 1) {
							 temp_util_obj.setU2(temp_util);
							 temp_ener_obj.setE2(temp_energ);
							 temp_temps_obj.setT2(temp_temps);
							 temp_ce_obj.setCE2(temp_ce);
							 temp_cc_obj.setCC2(temp_cc);
						 }
						 else {

							 utilites_CPU[ti.getCi()].setU2(utilites_CPU[ti.getCi()].getU2() + temp_util);
							 energies_CPU[ti.getCi()].setE2(energies_CPU[ti.getCi()].getE2() + temp_energ);
							 temps_CPU[ti.getCi()].setT2(temps_CPU[ti.getCi()].getT2() + temp_temps);
							 coutEnvoi_CPU[ti.getCi()].setCE2(coutEnvoi_CPU[ti.getCi()].getCE2() + temp_ce);
							 coutCalcul_CPU[ti.getCi()].setCC2(coutCalcul_CPU[ti.getCi()].getCC2() + temp_cc);
						 }

						 utilites_Delestage_SE.insert(std::pair<int, long double>(ti.getId(), temp_util));

						 if (temp_util < meilleurUtilite) {
							 meilleurStrategie = 2;
							 meilleurUtilite = temp_util;
							 meilleurEnergie = temp_energ;
							 meilleurTemps = temp_temps;
							 meilleurCoutEnvoi = temp_ce;
							 meilleurCoutCalcul = temp_cc;
						 }

						 //S3 : sharing with secondary drones
						 temp_util  =  calcul_partage_DS(ti,drone_pricipal, drones_secondaires);
						 temp_energ = getEnergieS3(ti,drone_pricipal, drones_secondaires);
						 temp_temps = getTempsS3(ti,drone_pricipal, drones_secondaires);
						 temp_ce = getCES3(ti);
						 temp_cc = getCCS3(ti);
						 if (iter == 1) {
							 temp_util_obj.setU3(temp_util);
							 temp_ener_obj.setE3(temp_energ);
							 temp_temps_obj.setT3(temp_temps);
							 temp_ce_obj.setCE3(temp_ce);
							 temp_cc_obj.setCC3(temp_cc);
						 }
						 else {

							 utilites_CPU[ti.getCi()].setU3(utilites_CPU[ti.getCi()].getU3() + temp_util);
							 energies_CPU[ti.getCi()].setE3(energies_CPU[ti.getCi()].getE3() + temp_energ);
							 temps_CPU[ti.getCi()].setT3(temps_CPU[ti.getCi()].getT3() + temp_temps);
							 coutEnvoi_CPU[ti.getCi()].setCE3(coutEnvoi_CPU[ti.getCi()].getCE3() + temp_ce);
							 coutCalcul_CPU[ti.getCi()].setCC3(coutCalcul_CPU[ti.getCi()].getCC3() + temp_cc);
						 }

						 utilites_Partage_DS.insert(std::pair<int, long double>(ti.getId(), temp_util));
						 if (temp_util < meilleurUtilite) {
							 meilleurStrategie = 3;
							 meilleurUtilite = temp_util;
							 meilleurEnergie = temp_energ;
							 meilleurTemps = temp_temps;
							 meilleurCoutEnvoi = temp_ce;
							 meilleurCoutCalcul = temp_cc;
						 }

						 //S4 : offloading to authority  vehicle + local computation in authority vehicle
						 temp_util  = calcul_local_VP(ti, vehicule_police);
						 temp_energ = getEnergieS4(ti, vehicule_police);
						 temp_temps = getTempsS4(ti, vehicule_police);
						 temp_ce = getCES4(ti);
						 temp_cc = getCCS4(ti);
						 if (iter == 1) {
							 temp_util_obj.setU4(temp_util);
							 temp_ener_obj.setE4(temp_energ);
							 temp_temps_obj.setT4(temp_temps);
							 temp_ce_obj.setCE4(temp_ce);
							 temp_cc_obj.setCC4(temp_cc);
						 }
						 else {

							 utilites_CPU[ti.getCi()].setU4(utilites_CPU[ti.getCi()].getU4() + temp_util);
							 energies_CPU[ti.getCi()].setE4(energies_CPU[ti.getCi()].getE4() + temp_energ);
							 temps_CPU[ti.getCi()].setT4(temps_CPU[ti.getCi()].getT4() + temp_temps);
							 coutEnvoi_CPU[ti.getCi()].setCE4(coutEnvoi_CPU[ti.getCi()].getCE4() + temp_ce);
							 coutCalcul_CPU[ti.getCi()].setCC4(coutCalcul_CPU[ti.getCi()].getCC4() + temp_cc);
						 }

						 utilites_Local_VP.insert(std::pair<int, long double>(ti.getId(), temp_util));
						 if (temp_util < meilleurUtilite) {
							 meilleurStrategie = 4;
							 meilleurUtilite = temp_util;
							 meilleurEnergie = temp_energ;
							 meilleurTemps = temp_temps;
							 meilleurCoutEnvoi = temp_ce;
							 meilleurCoutCalcul = temp_cc;
						 }

						 //S5 : offloading to authority vehicle + offloading to Edge server by the authority vehicle
						 temp_util = calcul_delestage_VP_SE(ti, serveur_edge);
						 temp_energ = getEnergieS5(ti);
						 temp_temps = getTempsS5(ti, serveur_edge);
						 temp_ce = getCES5(ti);
						 temp_cc = getCCS5(ti);
						 if (iter == 1) {
							 temp_util_obj.setU5(temp_util);
							 temp_ener_obj.setE5(temp_energ);
							 temp_temps_obj.setT5(temp_temps);
							 temp_ce_obj.setCE5(temp_ce);
							 temp_cc_obj.setCC5(temp_cc);
						 }
						 else {

							 utilites_CPU[ti.getCi()].setU5(utilites_CPU[ti.getCi()].getU5() + temp_util);
							 energies_CPU[ti.getCi()].setE5(energies_CPU[ti.getCi()].getE5() + temp_energ);
							 temps_CPU[ti.getCi()].setT5(temps_CPU[ti.getCi()].getT5() + temp_temps);
							 coutEnvoi_CPU[ti.getCi()].setCE5(coutEnvoi_CPU[ti.getCi()].getCE5() + temp_ce);
							 coutCalcul_CPU[ti.getCi()].setCC5(coutCalcul_CPU[ti.getCi()].getCC5() + temp_cc);
						 }

						 utilites_VP_Delestage_SE.insert(std::pair<int, long double>(ti.getId(), temp_util));
						 if (temp_util < meilleurUtilite) {
							 meilleurStrategie = 5;
							 meilleurUtilite = temp_util;
							 meilleurEnergie = temp_energ;
							 meilleurTemps = temp_temps;
							 meilleurCoutEnvoi = temp_ce;
							 meilleurCoutCalcul = temp_cc;
						 }

						 //S6 : offloading to authority vehicle + sharing with nearby vehicle + accpet computation by nearby vehicle
						 temp_util = calcul_partage_VV_accpt(ti, vehicule_police, vehicule_voisin);
						 temp_energ = getEnergieS6(ti, vehicule_police, vehicule_voisin);
						 temp_temps = getTempsS6(ti, vehicule_voisin);
						 temp_ce = getCES6(ti);
						 temp_cc = getCCS6(ti);
						 if (iter == 1) {
							 temp_util_obj.setU6(temp_util);
							 temp_ener_obj.setE6(temp_energ);
							 temp_temps_obj.setT6(temp_temps);
							 temp_ce_obj.setCE6(temp_ce);
							 temp_cc_obj.setCC6(temp_cc);
						 }
						 else {

							 utilites_CPU[ti.getCi()].setU6(utilites_CPU[ti.getCi()].getU6() + temp_util);
							 energies_CPU[ti.getCi()].setE6(energies_CPU[ti.getCi()].getE6() + temp_energ);
							 temps_CPU[ti.getCi()].setT6(temps_CPU[ti.getCi()].getT6() + temp_temps);
							 coutEnvoi_CPU[ti.getCi()].setCE6(coutEnvoi_CPU[ti.getCi()].getCE6() + temp_ce);
							 coutCalcul_CPU[ti.getCi()].setCC6(coutCalcul_CPU[ti.getCi()].getCC6() + temp_cc);
						 }

						 utilites_VP_Partage_VV_accpt.insert(std::pair<int, long double>(ti.getId(), temp_util));
						 if (temp_util < meilleurUtilite) {
							 meilleurStrategie = 6;
							 meilleurUtilite = temp_util;
							 meilleurEnergie = temp_energ;
							 meilleurTemps = temp_temps;
							 meilleurCoutEnvoi = temp_ce;
							 meilleurCoutCalcul = temp_cc;
						 }
						 //S7 : offloading to authority vehicle + sharing with nearby vehicle + refuse computation by nearby vehicle
						 temp_util = calcul_partage_VV_refu(ti, vehicule_police);
						 temp_energ = getEnergieS7(ti,vehicule_police);
						 temp_temps = getTempsS7(ti, vehicule_police);
						 temp_ce = getCES7(ti);
						 temp_cc = getCCS7(ti);
						 if (iter == 1) {
							 temp_util_obj.setU7(temp_util);
							 temp_ener_obj.setE7(temp_energ);
							 temp_temps_obj.setT7(temp_temps);
							 temp_ce_obj.setCE7(temp_ce);
							 temp_cc_obj.setCC7(temp_cc);

						 }
						 else {

							 utilites_CPU[ti.getCi()].setU7(utilites_CPU[ti.getCi()].getU7() + temp_util);
							 energies_CPU[ti.getCi()].setE7(energies_CPU[ti.getCi()].getE7() + temp_energ);
							 temps_CPU[ti.getCi()].setT7(temps_CPU[ti.getCi()].getT7() + temp_temps);
							 coutEnvoi_CPU[ti.getCi()].setCE7(coutEnvoi_CPU[ti.getCi()].getCE7() + temp_ce);
							 coutCalcul_CPU[ti.getCi()].setCC7(coutCalcul_CPU[ti.getCi()].getCC7() + temp_cc);
						 }

						 utilites_VP_Partage_VV_refu.insert(std::pair<int, long double>(ti.getId(), temp_util));
						 if (temp_util < meilleurUtilite) {
							 meilleurStrategie = 7;
							 meilleurUtilite = temp_util;
							 meilleurEnergie = temp_energ;
							 meilleurTemps = temp_temps;
							 meilleurCoutEnvoi = temp_ce;
							 meilleurCoutCalcul = temp_cc;
						 }

						 if (iter == 1) {
							 temp_util_obj.setGt(meilleurUtilite);
							 temp_ener_obj.setGt(meilleurEnergie);
							 temp_temps_obj.setGt(meilleurTemps);
							 temp_ce_obj.setGt(meilleurCoutEnvoi);
							 temp_cc_obj.setGt(meilleurCoutCalcul);
						 }
						 else {

							 utilites_CPU[ti.getCi()].setGt(utilites_CPU[ti.getCi()].getGt() + meilleurUtilite);
							 energies_CPU[ti.getCi()].setGt(energies_CPU[ti.getCi()].getGt() + meilleurEnergie);
							 temps_CPU[ti.getCi()].setGt(temps_CPU[ti.getCi()].getGt() + meilleurTemps);
							 coutEnvoi_CPU[ti.getCi()].setGt(coutEnvoi_CPU[ti.getCi()].getGt() + meilleurCoutEnvoi);
							 coutCalcul_CPU[ti.getCi()].setGt(coutCalcul_CPU[ti.getCi()].getGt() + meilleurCoutCalcul);
						 }

						 if (iter == 1) {
							 utilites_CPU.insert(std::pair<long double, Utilite>(ti.getCi(), temp_util_obj));
							 energies_CPU.insert(std::pair<long double, Energie>(ti.getCi(), temp_ener_obj));
							 temps_CPU.insert(std::pair<long double, Temps>(ti.getCi(), temp_temps_obj));
							 coutEnvoi_CPU.insert(std::pair<long double, CoutEnvoie>(ti.getCi(), temp_ce_obj));
							 coutCalcul_CPU.insert(std::pair<long double, CoutCalcul>(ti.getCi(), temp_cc_obj));
						 }


						 std::cout << "Ci " << ti.getCi() << " Di " << ti.getDi() << " Rsi " << ti.getRsi() << " Meuilleur Decision:" << meilleurStrategie << '\n';

						 

						 std::cout << "Tache num " << ti.getId() << "Ci" << ti.getCi() << " U1  " << utilites_CPU[ti.getCi()].getU1() << " U2 " << utilites_CPU[ti.getCi()].getU2() << " U3 " << utilites_CPU[ti.getCi()].getU3() << " U4 " << utilites_CPU[ti.getCi()].getU4() << " U5 " << utilites_CPU[ti.getCi()].getU5() << " U6 " << utilites_CPU[ti.getCi()].getU6() << "U7 " << utilites_CPU[ti.getCi()].getU7() << "Meuilleur S" << utilites_CPU[ti.getCi()].getGt() << '\n';

					 }


					 iter++;




					 cycle_cpu = cycle_cpu_var;
					 tailleDonnee = tailleDonnee * 2;
				 }


				 cycle_cpu = cycle_cpu_var;
				 max_cycle_cpu = max_cycle_cpu_var;
				 taille_resultat = taille_resultat_var;
				 tailleDonnee = tailleDonnee_var;
				 maxTaille = maxTaille_var;
				 // Loop for initializing the values of the tasks to be calculated as such Ci =[500000,...,10000000], Di=5Mo, Rsi=5ko
				 iter = 1;
				 // matrice pour stocker l'utilité de chaque strategie+GT selon le changement de cycle CPU  [Cycle_CPU, [U1,U2,U3,U4,U5,U6,U7,GT]] 
				 std::map<long double, Utilite> utilites_Donnees;
				 std::map<long double, Energie> energie_Donnees;
				 std::map<long double, Temps> temps_Donnees;
				 std::map<long double, CoutEnvoie> coutEnvoi_Donnees;
				 std::map<long double, CoutCalcul> coutCalcul_Donnees;
				 while (cycle_cpu <= max_cycle_cpu)
				 {
					 int i = 0;
					 taches.clear();
					 while (tailleDonnee <= maxTaille)
					 {
						 Tache tachei(i, cycle_cpu, tailleDonnee, taille_resultat, 1);
						 taches.push_back(tachei);
						 tailleDonnee = tailleDonnee * 2;
						 i++;
					 }



					 std::multimap < int, Tache> ::iterator itr;
					 int meilleurStrategie;// variable used to store the strategy having the best utility for each task
					 long double meilleurUtilite;
					 long double meilleurEnergie;
					 long double meilleurTemps;
					 long double meilleurCoutEnvoi;
					 long double meilleurCoutCalcul;
					 long double temp_util = 0;
					 long double temp_energ = 0;
					 long double temp_temps = 0;
					 long double temp_ce = 0;
					 long double temp_cc = 0;

					 for (int c = 0; c < taches.size(); c++)
					 {
						 Utilite temp_util_obj;
						 Energie temp_energ_obj;
						 Temps temp_temps_obj;
						 CoutEnvoie temp_ce_obj;
						 CoutCalcul temp_cc_obj;
						 Tache ti = taches[c];
						 meilleurStrategie = 1;
						 meilleurUtilite = 0;
						 meilleurEnergie = 0;
						 meilleurTemps = 0;
						 meilleurCoutEnvoi = 0;
						 meilleurCoutCalcul = 0;
						 // S1 : local computation
						 temp_util = calcul_local_DP(ti, drone_pricipal);
						 temp_energ = getEnergieS1(ti, drone_pricipal);
						 temp_temps = getTempsS1(ti,drone_pricipal);
						 temp_ce = getCES1(ti);
						 temp_cc = getCCS1(ti);
						 if (iter == 1) {
							 temp_util_obj.setU1(temp_util);
							 temp_energ_obj.setE1(temp_energ);
							 temp_temps_obj.setT1(temp_temps);
							 temp_ce_obj.setCE1(temp_ce);
							 temp_cc_obj.setCC1(temp_cc);
						 }
						 else {

							 utilites_Donnees[ti.getDi()].setU1(utilites_Donnees[ti.getDi()].getU1() + temp_util);
							 energie_Donnees[ti.getDi()].setE1(energie_Donnees[ti.getDi()].getE1() + temp_energ);
							 temps_Donnees[ti.getDi()].setT1(temps_Donnees[ti.getDi()].getT1() + temp_temps);
							 coutEnvoi_Donnees[ti.getDi()].setCE1(coutEnvoi_Donnees[ti.getDi()].getCE1() + temp_ce);
							 coutCalcul_Donnees[ti.getDi()].setCC1(coutCalcul_Donnees[ti.getDi()].getCC1() + temp_cc);
						 }

						 utilites_Local.insert(std::pair<int, long double>(ti.getId(), temp_util));
						 meilleurUtilite = temp_util;
						 meilleurEnergie = temp_energ;
						 meilleurTemps = temp_temps;
						 meilleurCoutEnvoi = temp_ce;
						 meilleurCoutCalcul = temp_cc;
						 // S2 : offloading to Edge server
						 temp_util = calcul_delestage_SE(ti, serveur_edge);
						 temp_energ = getEnergieS2(ti);
						 temp_temps = getTempsS2(ti, serveur_edge);
						 temp_ce = getCES2(ti);
						 temp_cc = getCCS2(ti);
						 if (iter == 1) {
							 temp_util_obj.setU2(temp_util);
							 temp_energ_obj.setE2(temp_energ);
							 temp_temps_obj.setT2(temp_temps);
							 temp_ce_obj.setCE2(temp_ce);
							 temp_cc_obj.setCC2(temp_cc);
						 }
						 else {

							 utilites_Donnees[ti.getDi()].setU2(utilites_Donnees[ti.getDi()].getU2() + temp_util);
							 energie_Donnees[ti.getDi()].setE2(energie_Donnees[ti.getDi()].getE2() + temp_energ);
							 temps_Donnees[ti.getDi()].setT2(temps_Donnees[ti.getDi()].getT2() + temp_temps);
							 coutEnvoi_Donnees[ti.getDi()].setCE2(coutEnvoi_Donnees[ti.getDi()].getCE2() + temp_ce);
							 coutCalcul_Donnees[ti.getDi()].setCC2(coutCalcul_Donnees[ti.getDi()].getCC2() + temp_cc);
						 }

						 utilites_Delestage_SE.insert(std::pair<int, long double>(ti.getId(), temp_util));

						 if (temp_util < meilleurUtilite) {
							 meilleurStrategie = 2;
							 meilleurUtilite = temp_util;
							 meilleurEnergie = temp_energ;
							 meilleurTemps = temp_temps;
							 meilleurCoutEnvoi = temp_ce;
							 meilleurCoutCalcul = temp_cc;
						 }

						 //S3 : sharing with secondary drones
						 temp_util = calcul_partage_DS(ti, drone_pricipal, drones_secondaires);
						 temp_energ = getEnergieS3(ti, drone_pricipal, drones_secondaires);
						 temp_temps = getTempsS3(ti, drone_pricipal, drones_secondaires);
						 temp_ce = getCES3(ti);
						 temp_cc = getCCS3(ti);
						 if (iter == 1) {
							 temp_util_obj.setU3(temp_util);
							 temp_energ_obj.setE3(temp_energ);
							 temp_temps_obj.setT3(temp_temps);
							 temp_ce_obj.setCE3(temp_ce);
							 temp_cc_obj.setCC3(temp_cc);
						 }
						 else {

							 utilites_Donnees[ti.getDi()].setU3(utilites_Donnees[ti.getDi()].getU3() + temp_util);
							 energie_Donnees[ti.getDi()].setE3(energie_Donnees[ti.getDi()].getE3() + temp_energ);
							 temps_Donnees[ti.getDi()].setT3(temps_Donnees[ti.getDi()].getT3() + temp_temps);
							 coutEnvoi_Donnees[ti.getDi()].setCE3(coutEnvoi_Donnees[ti.getDi()].getCE3() + temp_ce);
							 coutCalcul_Donnees[ti.getDi()].setCC3(coutCalcul_Donnees[ti.getDi()].getCC3() + temp_cc);
						 }

						 utilites_Partage_DS.insert(std::pair<int, long double>(ti.getId(), temp_util));
						 if (temp_util < meilleurUtilite) {
							 meilleurStrategie = 3;
							 meilleurUtilite = temp_util;
							 meilleurEnergie = temp_energ;
							 meilleurTemps = temp_temps;
							 meilleurCoutEnvoi = temp_ce;
							 meilleurCoutCalcul = temp_cc;
						 }

						 //S4 : offloading to authority  vehicle + local computation in authority vehicle
						 temp_util = calcul_local_VP(ti, vehicule_police);
						 temp_energ = getEnergieS4(ti,vehicule_police);
						 temp_temps = getTempsS4(ti, vehicule_police);
						 temp_ce = getCES4(ti);
						 temp_cc = getCCS4(ti);
						 if (iter == 1) {
							 temp_util_obj.setU4(temp_util);
							 temp_energ_obj.setE4(temp_energ);
							 temp_temps_obj.setT4(temp_temps);
							 temp_ce_obj.setCE4(temp_ce);
							 temp_cc_obj.setCC4(temp_cc);
						 }
						 else {

							 utilites_Donnees[ti.getDi()].setU4(utilites_Donnees[ti.getDi()].getU4() + temp_util);
							 energie_Donnees[ti.getDi()].setE4(energie_Donnees[ti.getDi()].getE4() + temp_energ);
							 temps_Donnees[ti.getDi()].setT4(temps_Donnees[ti.getDi()].getT4() + temp_temps);
							 coutEnvoi_Donnees[ti.getDi()].setCE4(coutEnvoi_Donnees[ti.getDi()].getCE4() + temp_ce);
							 coutCalcul_Donnees[ti.getDi()].setCC4(coutCalcul_Donnees[ti.getDi()].getCC4() + temp_cc);
						 }

						 utilites_Local_VP.insert(std::pair<int, long double>(ti.getId(), temp_util));
						 if (temp_util < meilleurUtilite) {
							 meilleurStrategie = 4;
							 meilleurUtilite = temp_util;
							 meilleurEnergie = temp_energ;
							 meilleurTemps = temp_temps;
							 meilleurCoutEnvoi = temp_ce;
							 meilleurCoutCalcul = temp_cc;
						 }

						 //S5 : offloading to authority vehicle + offloading to Edge server by the authority vehicle
						 temp_util = calcul_delestage_VP_SE(ti, serveur_edge);
						 temp_energ = getEnergieS5(ti);
						 temp_temps = getTempsS5(ti, serveur_edge);
						 temp_ce = getCES5(ti);
						 temp_cc = getCCS5(ti);
						 if (iter == 1) {
							 temp_util_obj.setU5(temp_util);
							 temp_energ_obj.setE5(temp_energ);
							 temp_temps_obj.setT5(temp_temps);
							 temp_ce_obj.setCE5(temp_ce);
							 temp_cc_obj.setCC5(temp_cc);
						 }
						 else {

							 utilites_Donnees[ti.getDi()].setU5(utilites_Donnees[ti.getDi()].getU5() + temp_util);
							 energie_Donnees[ti.getDi()].setE5(energie_Donnees[ti.getDi()].getE5() + temp_energ);
							 temps_Donnees[ti.getDi()].setT5(temps_Donnees[ti.getDi()].getT5() + temp_temps);
							 coutEnvoi_Donnees[ti.getDi()].setCE5(coutEnvoi_Donnees[ti.getDi()].getCE5() + temp_ce);
							 coutCalcul_Donnees[ti.getDi()].setCC5(coutCalcul_Donnees[ti.getDi()].getCC5() + temp_cc);
						 }

						 utilites_VP_Delestage_SE.insert(std::pair<int, long double>(ti.getId(), temp_util));
						 if (temp_util < meilleurUtilite) {
							 meilleurStrategie = 5;
							 meilleurUtilite = temp_util;
							 meilleurEnergie = temp_energ;
							 meilleurTemps = temp_temps;
							 meilleurCoutEnvoi = temp_ce;
							 meilleurCoutCalcul = temp_cc;
						 }

						 //S6 :  offloading to authority vehicle + sharing with nearby vehicle + accpet computation by nearby vehicle
						 temp_util = calcul_partage_VV_accpt(ti, vehicule_police, vehicule_voisin);
						 temp_energ = getEnergieS6(ti, vehicule_police, vehicule_voisin);
						 temp_temps = getTempsS6(ti, vehicule_voisin);
						 temp_ce = getCES6(ti);
						 temp_cc = getCCS6(ti);
						 if (iter == 1) {
							 temp_util_obj.setU6(temp_util);
							 temp_energ_obj.setE6(temp_energ);
							 temp_temps_obj.setT6(temp_temps);
							 temp_ce_obj.setCE6(temp_ce);
							 temp_cc_obj.setCC6(temp_cc);
						 }
						 else {

							 utilites_Donnees[ti.getDi()].setU6(utilites_Donnees[ti.getDi()].getU6() + temp_util);
							 energie_Donnees[ti.getDi()].setE6(energie_Donnees[ti.getDi()].getE6() + temp_energ);
							 temps_Donnees[ti.getDi()].setT6(temps_Donnees[ti.getDi()].getT6() + temp_temps);
							 coutEnvoi_Donnees[ti.getDi()].setCE6(coutEnvoi_Donnees[ti.getDi()].getCE6() + temp_ce);
							 coutCalcul_Donnees[ti.getDi()].setCC6(coutCalcul_Donnees[ti.getDi()].getCC6() + temp_cc);
						 }

						 utilites_VP_Partage_VV_accpt.insert(std::pair<int, long double>(ti.getId(), temp_util));
						 if (temp_util < meilleurUtilite) {
							 meilleurStrategie = 6;
							 meilleurUtilite = temp_util;
							 meilleurEnergie = temp_energ;
							 meilleurTemps = temp_temps;
							 meilleurCoutEnvoi = temp_ce;
							 meilleurCoutCalcul = temp_cc;
						 }
						 //S7 :  offloading to authority vehicle + sharing with nearby vehicle + refuse computation by nearby vehicle
						 temp_util = calcul_partage_VV_refu(ti, vehicule_police);
						 temp_energ = getEnergieS7(ti, vehicule_police);
						 temp_temps = getTempsS7(ti, vehicule_police);
						 temp_ce = getCES7(ti);
						 temp_cc = getCCS7(ti);
						 if (iter == 1) {
							 temp_util_obj.setU7(temp_util);
							 temp_energ_obj.setE7(temp_energ);
							 temp_temps_obj.setT7(temp_temps);
							 temp_ce_obj.setCE7(temp_ce);
							 temp_cc_obj.setCC7(temp_cc);
						 }
						 else {

							 utilites_Donnees[ti.getDi()].setU7(utilites_Donnees[ti.getDi()].getU7() + temp_util);
							 energie_Donnees[ti.getDi()].setE7(energie_Donnees[ti.getDi()].getE7() + temp_energ);
							 temps_Donnees[ti.getDi()].setT7(temps_Donnees[ti.getDi()].getT7() + temp_temps);
							 coutEnvoi_Donnees[ti.getDi()].setCE7(coutEnvoi_Donnees[ti.getDi()].getCE7() + temp_ce);
							 coutCalcul_Donnees[ti.getDi()].setCC7(coutCalcul_Donnees[ti.getDi()].getCC7() + temp_cc);
						 }

						 utilites_VP_Partage_VV_refu.insert(std::pair<int, long double>(ti.getId(), temp_util));
						 if (temp_util < meilleurUtilite) {
							 meilleurStrategie = 7;
							 meilleurUtilite = temp_util;
							 meilleurEnergie = temp_energ;
							 meilleurTemps = temp_temps;
							 meilleurCoutEnvoi = temp_ce;
							 meilleurCoutCalcul = temp_cc;
						 }

						 if (iter == 1) {
							 temp_util_obj.setGt(meilleurUtilite);
							 temp_energ_obj.setGt(meilleurEnergie);
							 temp_temps_obj.setGt(meilleurTemps);
							 temp_ce_obj.setGt(meilleurCoutEnvoi);
							 temp_cc_obj.setGt(meilleurCoutCalcul);
						 }
						 else {

							 utilites_Donnees[ti.getDi()].setGt(utilites_Donnees[ti.getDi()].getGt() + meilleurUtilite);
							 energie_Donnees[ti.getDi()].setGt(energie_Donnees[ti.getDi()].getGt() + meilleurEnergie);
							 temps_Donnees[ti.getDi()].setGt(temps_Donnees[ti.getDi()].getGt() + meilleurTemps);
							 coutEnvoi_Donnees[ti.getDi()].setGt(coutEnvoi_Donnees[ti.getDi()].getGt() + meilleurCoutEnvoi);
							 coutCalcul_Donnees[ti.getDi()].setGt(coutCalcul_Donnees[ti.getDi()].getGt() + meilleurCoutCalcul);
						 }

						 if (iter == 1) {
							 utilites_Donnees.insert(std::pair<long double, Utilite>(ti.getDi(), temp_util_obj));
							 energie_Donnees.insert(std::pair<long double, Energie>(ti.getDi(), temp_energ_obj));
							 temps_Donnees.insert(std::pair<long double, Temps>(ti.getDi(), temp_temps_obj));
							 coutEnvoi_Donnees.insert(std::pair<long double, CoutEnvoie>(ti.getDi(), temp_ce_obj));
							 coutCalcul_Donnees.insert(std::pair<long double, CoutCalcul>(ti.getDi(), temp_cc_obj));
						 }


						

						 std::cout << "Tache num " << ti.getId() << " Ci: " << ti.getCi() << " Di: " << ti.getDi() << " U1  " << utilites_Donnees[ti.getDi()].getU1() << " U2 " << utilites_Donnees[ti.getDi()].getU2() << " U3 " << utilites_Donnees[ti.getDi()].getU3() << " U4 " << utilites_Donnees[ti.getDi()].getU4() << " U5 " << utilites_Donnees[ti.getDi()].getU5() << " U6 " << utilites_Donnees[ti.getDi()].getU6() << "U7 " << utilites_Donnees[ti.getDi()].getU7() << "Meuilleur S" << meilleurStrategie << '\n';

					 }


					 iter++;




					 cycle_cpu = cycle_cpu * 2;
					 tailleDonnee = tailleDonnee_var;
				 }

				 taches.clear();

				 std::cout << "MaxT: " << maxT << " minT: " << minT << " maxE: " << maxE << " minE: " << minE << " maxCE: " << maxCE << " minCE: " << minCE << " maxCC: " << maxCC << " minCC: " << minCC << "\n";

			 }




	};



	
}
