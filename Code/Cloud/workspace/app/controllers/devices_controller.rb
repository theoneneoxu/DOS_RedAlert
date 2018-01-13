class DevicesController < ApplicationController
  skip_before_filter :verify_authenticity_token
  before_action :set_device, only: [:show, :edit, :update, :destroy]

  # GET /devices
  # GET /devices.json
  def index
    @devices = Device.all
  end

  # GET /devices/1
  # GET /devices/1.json
  def show
  end

  # GET /devices/new
  def new
    @device = Device.new
  end

  # GET /devices/1/edit
  def edit
  end

  # POST /devices
  # POST /devices.json
  def create
    @device = Device.new(device_params)
    @result=Device.find_by ip: device_params[:ip]
    if @result==nil
      @device.save
    else
    end
    respond_to do |format|
      if @result==nil
        format.html { render plain: "OK"}
      else
        format.html { render plain: "Already Exist" }
      end
    end
  end

  # PATCH/PUT /devices/1
  # PATCH/PUT /devices/1.json
  def update
    respond_to do |format|
      if @device.update(device_params)
        format.html { redirect_to @device, notice: 'Device was successfully updated.' }
        format.json { render :show, status: :ok, location: @device }
      else
        format.html { render :edit }
        format.json { render json: @device.errors, status: :unprocessable_entity }
      end
    end
  end

  # DELETE /devices/1
  # DELETE /devices/1.json
  def destroy
    @device.destroy
    respond_to do |format|
      format.html { redirect_to devices_url, notice: 'Device was successfully destroyed.' }
      format.json { head :no_content }
    end
  end
  def device_online
    device=Device.find_by ip: device_params[:ip]
    device.status='Online'
    device.save
    render plain: "OK"
  end
  def device_offline
    device=Device.find_by ip: device_params[:ip]
    device.status='Offline'
    device.save
    render plain: "OK"
  end
  def sensor_alarm
    device=Device.find_by ip: device_params[:ip]
    device.alarm_by_sensor='On'
    device.save
    render plain: "OK"
  end
  def button_alarm
    device=Device.find_by ip: device_params[:ip]
    device.alarm_by_button='On'
    device.save
    render plain: "OK"
  end
  def dismiss
    u1 = UDPSocket.new
    u1.send "3100", 0, "192.168.19.102", 35272
    Device.update_all "alarm_by_button = '', alarm_by_sensor = ''"
    redirect_to devices_url
  end
  def temp
    device=Device.find_by ip: device_params[:ip]
    device.temp=device_params[:temp]
    device.save
    render plain: "OK"
  end

  private
  # Use callbacks to share common setup or constraints between actions.
  def set_device
    @device = Device.find(params[:id])
  end

  # Never trust parameters from the scary internet, only allow the white list through.
  def device_params
    params.require(:device).permit(:name, :ip, :status, :alarm_by_button, :alarm_by_sensor, :alarm_status_time, :temp)
  end
end