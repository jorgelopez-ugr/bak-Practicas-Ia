list <Action> ComportamientoJugador::AnchuraLvl1(const stateN0 &inicio, const ubicacion &final, const vector<vector<unsigned char> > &mapa){
    
	nodeN0 nodo_general;
	list<nodeN0> cerrados;
	set<nodeN0> abiertos;
	bool haySolucion = false;

	//nodo general ahora mismo es el instante inicial
	nodo_general.st = inicio;

	cerrados.push_back(nodo_general);

    vector<Action> acciones_posibles = {actIDLE, actWALK, actRUN, actTURN_L, actTURN_SR, act_CLB_WALK, act_CLB_TURN_SR};

	while (!haySolucion && !cerrados.empty())
	{
		nodo_general = cerrados.front();

		cout << endl << "0 general:";
		nodo_general.toString();
		cout << endl;

		abiertos.insert(nodo_general);
		cerrados.pop_front();

		cout << "esta el clb en rango de vision?" << endl;

		// if (colaboradorEnRangoVision(nodo_general.st.jugador,nodo_general.st.colaborador)){
		if (colaboradorEnRangoVision(nodo_general.st)){
			cout << "si le ve";
		}
		
		if (!(nodo_general.st.colaborador == final)){
			for (int i = 0 ; i < acciones_posibles.size() ;i++){ //vamos a generar todos los hijos posibles
				nodeN0 nodo_hijo = nodo_general;
				
				if(acciones_posibles[i] == act_CLB_WALK || acciones_posibles[i] == act_CLB_TURN_SR){
					// if (colaboradorEnRangoVision(nodo_general.st.jugador,nodo_general.st.colaborador)){
					if (colaboradorEnRangoVision(nodo_general.st)){

						cout << endl << "1:";
						nodo_hijo.toString();
						cout << endl;
						
						nodo_hijo.st = apply(acciones_posibles[i],nodo_general.st,mapa);
						nodo_hijo.secuencia.push_back(acciones_posibles[i]);

						cout << endl << "1.5:";
						nodo_hijo.toString();
						cout << endl;

						if (nodo_hijo.st.colaborador == final){
							cout << endl << "2:";
							nodo_hijo.toString();
							cout << endl;

							nodo_general = nodo_hijo;


							cout << endl << "3 general:";
							nodo_general.toString();
							cout << endl;


							haySolucion = true;
						}
					}
				}
				else
				{
					// if (colaboradorEnRangoVision(nodo_general.st.jugador,nodo_general.st.colaborador)){
					if (colaboradorEnRangoVision(nodo_general.st)){

						nodo_hijo.st = apply(actIDLE,nodo_general.st,mapa);
						nodo_hijo.secuencia.push_back(actIDLE);

						cout << endl << "3.5:";
						nodo_hijo.toString();
						cout << endl;
					}
					else
					{
						nodo_hijo.st = apply(acciones_posibles[i],nodo_general.st,mapa);
						nodo_hijo.secuencia.push_back(acciones_posibles[i]);	
					}
				}
				

				if (abiertos.find(nodo_hijo) == abiertos.end()){
					cerrados.push_back(nodo_hijo);
				}
			}
		}
		else
		{
			haySolucion = true;
		}
		
	}
	//aqui nodo general llega vacio
	cout << "Encontrado un plan: ";

	cout << endl << "final general: ";
	nodo_general.toString();
	cout << endl;

	PintaPlan(nodo_general.secuencia);

	return nodo_general.secuencia;
}
