
static double _DeltaTime;
static double _PrevFrameTime;

void calculate_delta_time(double rCurrentTime)
{
	_DeltaTime = rCurrentTime - _PrevFrameTime;
	_PrevFrameTime = rCurrentTime;
}

double get_delta_time()
{
	return _DeltaTime;
}