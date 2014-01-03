package com.truphone.cascades;

import java.io.PrintStream;

import org.junit.Assert;
import org.junit.Test;

import com.truphone.cascades.FakeDevice.FakeDeviceListener;
import com.truphone.cascades.commands.KeyCommand;
import com.truphone.cascades.replys.IReply;

/**
 * Test class.
 * @author STruscott
 *
 */
public final class TestKeyCommand {
	/**
	 * Test the key command.
	 * @throws TimeoutException Thrown if the command times out
	 */
	@Test
	public void testKeyCommand() throws TimeoutException {
		final FakeDeviceListener response = new FakeDeviceListener() {
			@Override
			public void messageReceived(String message, PrintStream replyStream) {
				if ("key 65 1 1 1 1".equals(message)) {
					replyStream.println(FakeDevice.OK_MESSAGE);
				} else {
					Assert.fail(message);
				}
			}
		};
		FakeDevice.DEVICE.getProcess().addListener(response);
		final IReply reply = FakeDevice.CONN.transmit(new KeyCommand('A', true, true, true, true), FakeDevice.DEFAULT_TIMEOUT);
		FakeDevice.DEVICE.getProcess().removeListener(response);
		Assert.assertTrue(reply.isSuccess());
	}
}