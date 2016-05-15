
#include "addon.h"
#include "gif-animation.h"

NAN_METHOD(Addon::runGif)
{
	Nan::HandleScope scope;
	
	if (_matrix == NULL) {
        return Nan::ThrowError("Matrix is not configured.");
	}
	
	int argc = info.Length();

	v8::Local<v8::Value> fileName  = Nan::Undefined();
	v8::Local<v8::Value> options   = Nan::Undefined();
	v8::Local<v8::Value> callback  = Nan::Undefined();

	if (argc > 0 && !info[0]->IsUndefined())
		fileName = v8::Local<v8::String>::Cast(info[0]);
	
	if (argc > 1 && info[1]->IsObject())
		options = v8::Local<v8::Value>::Cast(info[1]); 	 	
	
	if (argc > 2 && !info[2]->IsFunction())
		callback = v8::Local<v8::Value>::Cast(info[2]);

	
	GifAnimation *animation = new GifAnimation(_matrix);

	v8::Local<v8::Value> duration   = Nan::Undefined();
	v8::Local<v8::Value> delay      = Nan::Undefined();
	v8::Local<v8::Value> iterations = Nan::Undefined();

	if (!options->IsUndefined()) {
		v8::Local<v8::Object> object = v8::Local<v8::Object>::Cast(options);
		duration   = object->Get(Nan::New<v8::String>("duration").ToLocalChecked());
		delay      = object->Get(Nan::New<v8::String>("delay").ToLocalChecked());
		iterations = object->Get(Nan::New<v8::String>("iterations").ToLocalChecked());
	}

	if (!fileName->IsUndefined())
		animation->fileName(*v8::String::Utf8Value(fileName));

	if (!duration->IsUndefined()) {
		//int value = (v8::Local<v8::Integer>::Cast(duration))->IntegerValue();
		string strValue = *v8::String::Utf8Value(duration);
		
		fprintf(stdout, "string value is %s\n", strValue.c_str());
		
		int value = atoi(*v8::String::Utf8Value(duration));
		
		fprintf(stdout, "duration set to %d\n", value);
		animation->duration(value);
	}

	if (!iterations->IsUndefined()) {
		fprintf(stdout, "iterations set to %d\n", iterations->Int32Value());
		animation->iterations(iterations->Int32Value());
		
	}

	if (!delay->IsUndefined()) {
		fprintf(stdout, "delay set to %f\n", delay->NumberValue());
		animation->delay(delay->NumberValue());
		
	}

	runAnimation(animation, callback);


	info.GetReturnValue().Set(Nan::Undefined());
	
}

