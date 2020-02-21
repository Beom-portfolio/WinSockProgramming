#pragma once

// º¸°£
template<typename T1, typename T2>
const T1 Lerp(const T2& start, const T2& end, float process)
{
	return T1((1.f - process) * start + process * end);
}
