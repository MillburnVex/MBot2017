#ifndef AUTODUMP_H
#define AUTODUMP_H
namespace Autodump {
void Start();

void Cancel();

void UpdateControls();

bool IsActive();

void Update();

bool IsConeInFrontOfUltrasonic();
}
#endif
