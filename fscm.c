#include "fsmh.h"

int calc_time(int discret){
    static int time[] = {60,60,45,56,33,120,60,45,33,30,78,120,33,120,33,60,45,60,30,78,120,33,45,33,56,60,45,60,45,45,45,45,30, 60};

    int sum = 30;
    for(int i = 0 ;i < discret; i++){
        sum+= time[i];
    }
    return sum * 1000;
}


int skip(){
    if(t == calc_time(4)+1){
        t = calc_time(12);
        return 0;
    }
    if(t == calc_time(6)+1){
        t = calc_time(28);
        return 0;
    }
    if(t == calc_time(12)+1){
        t = calc_time(24);
        return 0;
    }
    if(t == calc_time(14)+1){
        t = calc_time(26);
        return 0;
    }
    if(t == calc_time(16)+1){
        t = calc_time(16)+2;
        return 0;
    }
    if(t == calc_time(8)+1){
        t = calc_time(26);
        return 0;
    }
}





void zero_chek(int zero_condition, struct Engine *engine, enum Input on, enum Input off){
    if(zero_condition){
        t++;
    } else{
        engine->state = STATE_ONE;
    }
}

void one_chek(int one_condition, struct Engine *engine, enum Input on, enum Input off){
    if(one_condition){
        t++;
    } else{
        engine->state = STATE_ZERO;
    }
}

void err_chek(int err_condition, struct Engine *engine, enum Input on, enum Input off){
    skip();
    if(err_condition == err_condition)
        engine->state = STATE_ERROR;
}

enum Output a_engine(struct Engine *engine0, enum Input input0, enum Input input1) // работа первого пневмоцилиндра
{
    struct Conditions a_cnd;
    a_cnd->zero_cnd = (input1 == INPUT_ZERO && input0 == INPUT_ONE && (t < calc_time(3) || (t > calc_time(5) && t < calc_time(11)) || (t > calc_time(13) && t < calc_time(19)) || (t > calc_time(21) && t < calc_time(25)) || (t > calc_time(27) && t < calc_time(29)) || (t > calc_time(31) && t < calc_time(33))));
    input1 == INPUT_ONE && input0 == INPUT_ZERO && ((t > calc_time(3) && t < calc_time(5)) || (t > calc_time(11) && t < calc_time(13)) || (t > calc_time(19) && t < calc_time(21)) || (t > calc_time(21) && t < calc_time(27)) || (t > calc_time(29) && t < calc_time(31)) || t > calc_time(34));

	switch (engine0->state) // engine отвечает за смену состояний
	{
	case STATE_ZERO: // состояние выключения
	{

        zero_chek(a_cnd->zero_cnd, engine0, input0, input1);

		// if (t < calc_time(3) || (t > calc_time(5) && t < calc_time(11)) || (t > calc_time(13) && t < calc_time(19)) || (t > calc_time(21) && t < calc_time(25)) || (t > calc_time(27) && t < calc_time(29)) || (t > calc_time(31) && t < calc_time(33))) // промежутки времени, в которые пневмоцилиндр выключен
		// {
		// 	t++; // увеличиваем значение таймера на один
		// }
		// else // если промежуток времени выключения закончился
		// {
		// 	engine0->state = STATE_ONE; // переход в состояние включения
		// }
		// if (t > 150000 && input0 == INPUT_ZERO) // одно из условий E (при ошибке переход не в состояние ошибки, а на другой шаг)
		// {
		// 	t = 770000; // переход на другой шаг работы
		// }
		// if (((t > 478000 && t < 511000) || (t > 656000 && t < 803000) || (t > 1151000 && t < 1108000) || (t > 1516000 && t < 1621000) || (t > 1473000 && t < 1551000) || (t > 1797000 && t < 1857000)) && input0 == INPUT_ZERO) // проверка работы пневмоцилиндра на ошибку, путем считывания сигнала с датчика, показывающего, что пневмоцилиндр выключен
		// {
		// 	engine0->state = STATE_ERROR; // переход в состояние ошибки при возникновении оной
		// }
		return OUTPUT_ZERO; // вывод нуля
	}
	case STATE_ONE: // состояние включения
	{
		if ((t > calc_time(3) && t < calc_time(5)) || (t > calc_time(11) && t < calc_time(13)) || (t > calc_time(19) && t < calc_time(21)) || (t > calc_time(21) && t < calc_time(27)) || (t > calc_time(29) && t < calc_time(31)) || t > calc_time(34) ) // промежутки времени, в которые пневмоцилиндр включен
		{
			t++; // увеличиваем значение таймера на один
		}
		else // если промежуток времени включения закончился
		{
			if (t >= 1951000) // если весь цикл закончился
			{
				t = 0;			   // переходим в начало работы системы
				return OUTPUT_ONE; // возвращаем один, чтобы не перейти в выключенное состояние, поскольку "дефолтным" является состояние включения
			}
			engine0->state = STATE_ZERO; // переход в состояние выключения
		}
		if (((t > 45000 && t < 75000) || (t > 232000 && t < 292000) || (t > 556000 && t < 611000) || (t > 925000 && t < 1003000) || (t > 1164000 && t < 1234000) || (t > 1372000 && t < 1417000) || (t > 1671000 && t < 1741000) || (t > 1902000 && t < 1947000)) && input1 == INPUT_ZERO) // проверка работы пневмоцилиндра на ошибку, путем считывания сигнала с датчика, показывающего, что пневмоцилиндр включен
		{
			engine0->state = STATE_ERROR; // переход в состояние ошибки при возникновении оной
		}
		return OUTPUT_ONE; // вывод единицы
	}
	case STATE_ERROR: // состояние ошибки
	{
		t = 0;				// возврат в начало работы программы
		return OUTPUT_ZERO; // возвращаем ноль
	}
	}
}

enum Output b_engine(struct Engine *engine1, enum Input input2, enum Input input3)
{
	switch (engine1->state)
	{
	case STATE_ZERO:
	{
		if (t < 90000 || (t > 446000 && t < 542000) || (t > 803000 && t < 1061000) || (t > 1151000 && t < 1349000) || (t > 1427000 && t < 1621000) || (t > 1726000 && t < 1816000))
		{
			t++;
		}
		else
		{
			if (t >= 1951000)
			{
				t = 0;
			}
			engine1->state = STATE_ONE;
		}
		if (t > 131000 && t < 176000 && input2 == INPUT_ZERO)
		{
			t = 422000;
		}
		if (((t > 478000 && t < 511000) || (t > 656000 && t < 689000) || (t > 1063000 && t < 1108000) || (t > 1294000 && t < 1327000) || (t > 1671000 && t < 1741000) || (t > 1902000 && t < 1947000)) && input2 == INPUT_ZERO)
		{
			engine1->state = STATE_ERROR;
		}
		return OUTPUT_ZERO;
	}
	case STATE_ONE:
	{
		if ((t > 90000 && t < 446000) || (t > 542000 && t < 803000) || (t > 1061000 && t < 1151000) || (t > 1349000 && t < 1427000) || (t > 1621000 && t < 1726000) || (t > 1816000 && t < 1951000))
		{
			t++;
		}
		else
		{
			engine1->state = STATE_ZERO;
		}
		if (t > 352000 && t < 422000 && input3 == INPUT_ZERO)
		{
			t = 1857000;
		}
		if (((t > 45000 && t < 75000) || (t > 556000 && t < 611000) || (t > 925000 && t < 1003000) || (t > 1164000 && t < 1234000) || (t > 1372000 && t < 1417000) || (t > 1797000 && t < 1857000)) && input3 == INPUT_ZERO)
		{
			engine1->state = STATE_ERROR;
		}
		return OUTPUT_ONE;
	}
	case STATE_ERROR:
	{
		t = 0;
		return OUTPUT_ZERO;
	}
	}
}

enum Output c_engine(struct Engine *engine2, enum Input input4, enum Input input5)
{
	switch (engine2->state)
	{
	case STATE_ZERO:
	{
		if (t < 464000 || (t > 650000 && t < 803000) || (t > 1349000 && t < 1427000) || (t > 1516000 && t < 1727000) || (t > 1891000 && t < 1951000))
		{
			t++;
		}
		else
		{
			if (t >= 1951000)
			{
				t = 0;
			}
			engine2->state = STATE_ONE;
		}
		if (t > 352000 && t < 422000 && input4 == INPUT_ZERO)
		{
			t = 1857000;
		}
		if (((t > 556000 && t < 611000) || (t > 1063000 && t < 1108000) || (t > 1349000 && t < 1417000) || (t > 1671000 && t < 1741000) || (t > 1902000 && t < 1947000)) && input4 == INPUT_ZERO)
		{
			engine2->state = STATE_ERROR;
		}
		return OUTPUT_ZERO;
	}
	case STATE_ONE:
	{
		if ((t > 464000 && t < 650000) || (t > 803000 && t < 1349000) || (t > 1427000 && t < 1516000) || (t > 1727000 && t < 1891000))
		{
			t++;
		}
		else
		{
			engine2->state = STATE_ZERO;
		}
		if (((t > 45000 && t < 75000) || (t > 478000 && t < 511000) || (t > 925000 && t < 1003000) || (t > 1294000 && t < 1327000) || (t > 1473000 && t < 1551000) || (t > 1797000 && t < 1857000)) && input5 == INPUT_ZERO)
		{
			engine2->state = STATE_ERROR;
		}
		return OUTPUT_ONE;
	}
	case STATE_ERROR:
	{
		t = 0;
		return OUTPUT_ZERO;
	}
	}
}

enum Output d_engine(struct Engine *engine3, enum Input input6, enum Input input7)
{
	switch (engine3->state)
	{
	case STATE_ZERO:
	{
		if (t < 284000 || (t > 542000 && t < 650000) || (t > 803000 && t < 1151000) || (t > 1349000 && t < 1427000) || (t > 1516000 && t < 1621000) || (t > 1726000 && t < 1816000))
		{
			t++;
		}
		else
		{
			if (t >= 1951000)
			{
				t = 0;
			}
			engine3->state = STATE_ONE;
		}
		if (((t > 284000 && t < 511000) || (t > 656000 && t < 689000) || (t > 1151000 && t < 1349000) || (t > 1427000 && t < 1516000) || (t > 1621000 && t < 1726000) || (t > 1816000 && t < 1891000)) && input6 == INPUT_ZERO)
		{
			engine3->state = STATE_ERROR;
		}
		return OUTPUT_ZERO;
	}
	case STATE_ONE:
	{
		if ((t > 284000 && t < 542000) || (t > 650000 && t < 803000) || (t > 1151000 && t < 1349000) || (t > 1427000 && t < 1516000) || (t > 1621000 && t < 1726000) || (t > 1816000 && t < 1951000))
		{
			t++;
		}
		else
		{
			engine3->state = STATE_ZERO;
		}
		if (((t > 45000 && t < 75000) || (t > 556000 && t < 611000) || (t > 809000 && t < 869000) || (t > 1063000 && t < 1108000) || (t > 1372000 && t < 1417000) || (t > 1797000 && t < 1857000)) && input7 == INPUT_ZERO)
		{
			engine3->state = STATE_ERROR;
		}
		return OUTPUT_ONE;
	}
	case STATE_ERROR:
	{
		t = 0;
		return OUTPUT_ZERO;
	}
	}
}

enum Output e_engine(struct Engine *engine4, enum Input input8, enum Input input9)
{
	switch (engine4->state)
	{
	case STATE_ZERO:
	{
		if (t < 90000 || (t > 195000 && t < 284000) || (t > 650000 && t < 803000) || (t > 1151000 && t < 1349000) || (t > 1427000 && t < 1621000) || (t > 1726000 && t < 1816000))
		{
			t++;
		}
		else
		{
			if (t >= 1951000)
			{
				t = 0;
			}
			engine4->state = STATE_ONE;
		}
		if (((t > 232000 && t < 292000) || (t > 478000 && t < 511000) || (t > 1063000 && t < 1108000) || (t > 1372000 && t < 1417000) || (t > 1671000 && t < 1741000) || (t > 1902000 && t < 1947000)) && input8 == INPUT_ZERO)
		{
			engine4->state = STATE_ERROR;
		}
		return OUTPUT_ZERO;
	}
	case STATE_ONE:
	{
		if ((t > 90000 && t < 195000) || (t > 284000 && t < 650000) || (t > 803000 && t < 1151000) || (t > 1349000 && t < 1427000) || (t > 1621000 && t < 1726000) || (t > 1816000 && t < 1951000))
		{
			t++;
		}
		else
		{
			engine4->state = STATE_ZERO;
		}
		if (t > 352000 && t < 422000 && input9 == INPUT_ZERO)
		{
			t = 1857000;
		}
		if (((t > 45000 && t < 75000) || (t > 556000 && t < 611000) || (t > 1294000 && t < 1327000) || (t > 1473000 && t < 1551000) || (t > 1797000 && t < 1857000)) && input9 == INPUT_ZERO)
		{
			engine4->state = STATE_ERROR;
		}
		return OUTPUT_ONE;
	}
	case STATE_ERROR:
	{
		t = 0;
		return OUTPUT_ZERO;
	}
	}
}

enum Output f_engine(struct Engine *engine5, enum Input input10, enum Input input11)
{
	switch (engine5->state)
	{
	case STATE_ZERO:
	{
		if (t < 90000 || (t > 284000 && t < 464000) || (t > 542000 && t < 650000) || (t > 803000 && t < 1061000) || (t > 1349000 && t < 1427000)|| (t > 1516000 && t < 1621000)|| (t > 1726000 && t < 1816000))
		{
			t++;
		}
		else
		{
			engine5->state = STATE_ONE;
		}
		if (((t > 556000 && t < 611000) || (t > 1063000 && t < 1108000) || (t > 1294000 && t < 1327000) || (t > 1473000 && t < 1551000) || (t > 1797000 && t < 1857000)) && input10 == INPUT_ZERO)
		{
			engine5->state = STATE_ERROR;
		}
		return OUTPUT_ZERO;
	}
	case STATE_ONE:
	{
		if ((t > 90000 && t < 284000) || (t > 464000 && t < 542000) || (t > 650000 && t < 803000) || (t > 1061000 && t < 1349000) || (t > 1427000 && t < 1516000)|| (t > 1621000 && t < 1726000)|| (t > 1816000 && t < 1951000))
		{
			t++;
		}
		else
		{
			if (t >= 1951000)
			{
				t = 0;
				return OUTPUT_ONE;
			}
			engine5->state = STATE_ZERO;
		}
		if (((t > 45000 && t < 75000) || (t > 925000 && t < 1003000) || (t > 1164000 && t < 1234000) || (t > 1372000 && t < 1417000) || (t > 1671000 && t < 1741000) || (t > 1902000 && t < 1947000)) && input11 == INPUT_ZERO)
		{
			engine5->state = STATE_ERROR;
		}
		return OUTPUT_ONE;
	}
	case STATE_ERROR:
	{
		t = 0;
		return OUTPUT_ZERO;
	}
	}
}

enum Output g_engine(struct Engine *engine6, enum Input input12, enum Input input13)
{
	switch (engine6->state)
	{
	case STATE_ZERO:
	{
		if (t < 650000 || (t > 803000 && t < 1061000) || (t > 1349000 && t < 1427000) || (t > 1516000 && t < 1621000) || (t > 1726000 && t < 1816000) )
		{
			t++;
		}
		else
		{
			if (t >= 1951000)
			{
				t = 0;
			}
			engine6->state = STATE_ONE;
		}
		if (t > 352000 && t < 422000 && input12 == INPUT_ZERO)
		{
			t = 1857000;
		}
		if (((t > 656000 && t < 689000) || (t > 1294000 && t < 1327000) || (t > 1671000 && t < 1741000) || (t > 1902000 && t < 1947000)) && input12 == INPUT_ZERO)
		{
			engine6->state = STATE_ERROR;
		}
		return OUTPUT_ZERO;
	}
	case STATE_ONE:
	{
		if ((t > 650000 && t < 803000) || (t > 1061000 && t < 1349000) || (t > 1427000 && t < 1516000) || (t > 1621000 && t < 1726000) || (t > 1816000 && t < 1951000))
		{
			t++;
		}
		else
		{
			engine6->state = STATE_ZERO;
		}
		if (t > 131000 && t < 176000 && input13 == INPUT_ZERO)
		{
			t = 422000;
		}
		if (((t > 556000 && t < 611000) || (t > 1063000 && t < 1108000) || (t > 1473000 && t < 1551000) || (t > 1797000 && t < 1857000)) && input13 == INPUT_ZERO)
		{
			engine6->state = STATE_ERROR;
		}
		return OUTPUT_ONE;
	}
	case STATE_ERROR:
	{
		t = 0;
		return OUTPUT_ZERO;
	}
	}
}

enum Output h_engine(struct Engine *engine7, enum Input input14, enum Input input15)
{
	switch (engine7->state)
	{
	case STATE_ZERO:
	{
		if (t < 90000 || (t >= 284000 && t < 464000) || (t >= 650000 && t < 956000) || (t >= 1427000 && t < 1621000) || (t >= 1726000 && t < 1816000))
		{
			t++;
		}
		else
		{
			if (t >= 1951000)
			{
				t = 0;
			}
			engine7->state = STATE_ONE;
		}
		if (((t > 556000 && t < 611000) || (t > 925000 && t < 1003000) || (t > 1473000 && t < 1551000) || (t > 1797000 && t < 1857000)) && input14 == INPUT_ZERO)
		{
			engine7->state = STATE_ERROR;
		}
		return OUTPUT_ZERO;
	}
	case STATE_ONE:
	{
		if ((t > 90000 && t < 284000) || (t >= 464000 && t < 650000) || (t >= 956000 && t < 1427000) || (t >= 1621000 && t < 1726000) || (t >= 1816000 && t < 1951000))
		{
			t++;
		}
		else
		{
			engine7->state = STATE_ZERO;
		}
		if (t > 131000 && t < 176000 && input15 == INPUT_ZERO)
		{
			t = 422000;
		}
		if (((t > 656000 && t < 689000) || (t > 1294000 && t < 1327000) || (t > 1671000 && t < 1741000)) && input15 == INPUT_ZERO)
		{
			engine7->state = STATE_ERROR;
		}
		return OUTPUT_ONE;
	}
	case STATE_ERROR:
	{
		t = 0;
		return OUTPUT_ZERO;
	}
	}
}

bool init0(struct Engine *engine0) // инициирующая функция
{
	if (0 == engine0)				// если ошибка
		return false;				// вернуть FALSE
	engine0->state = DEFAULT_STATE; // смена состояния на "дефолтное"
	return true;					// вернуть TRUE
}
bool init1(struct Engine *engine1)
{
	if (0 == engine1)
		return false;
	engine1->state = DEFAULT_STATE;
	return true;
}
bool init2(struct Engine *engine2)
{
	if (0 == engine2)
		return false;
	engine2->state = DEFAULT_STATE;
	return true;
}
bool init3(struct Engine *engine3)
{
	if (0 == engine3)
		return false;
	engine3->state = DEFAULT_STATE;
	return true;
}
bool init4(struct Engine *engine4)
{
	if (0 == engine4)
		return false;
	engine4->state = DEFAULT_STATE;
	return true;
}
bool init5(struct Engine *engine5)
{
	if (0 == engine5)
		return false;
	engine5->state = DEFAULT_STATE;
	return true;
}
bool init6(struct Engine *engine6)
{
	if (0 == engine6)
		return false;
	engine6->state = DEFAULT_STATE;
	return true;
}
bool init7(struct Engine *engine7)
{
	if (0 == engine7)
		return false;
	engine7->state = DEFAULT_STATE;
	return true;
}

bool reset0(struct Engine *engine0) // функция перезапуска
{
	return init0(engine0); // возвращаем функцию инициации
}
bool reset1(struct Engine *engine1)
{
	return init1(engine1);
}
bool reset2(struct Engine *engine2)
{
	return init2(engine2);
}
bool reset3(struct Engine *engine3)
{
	return init3(engine3);
}
bool reset4(struct Engine *engine4)
{
	return init4(engine4);
}
bool reset5(struct Engine *engine5)
{
	return init5(engine5);
}
bool reset6(struct Engine *engine6)
{
	return init6(engine6);
}
bool reset7(struct Engine *engine7)
{
	return init7(engine7);
}